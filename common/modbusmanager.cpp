#include "modbusmanager.h"
#include "modbusmap.h"

ModbusManager::ModbusManager(QObject *parent)
    : QObject{parent}
{

    this->client = new QModbusTcpClient(this);
    this->pollTimer = new QTimer(this);

    connect(client, &QModbusTcpClient::stateChanged,
            this, &ModbusManager::onStateChanged);

    // 定时器
    this->pollTimer->setInterval(1000);
    connect(pollTimer, &QTimer::timeout,
             this, &ModbusManager::pollTick);

}

ModbusManager::~ModbusManager()
{
    // client / pollTimer 都以 this 为父对象，由 QObject 析构链自动 delete，
    // 这里只需断开链路、停掉定时器，避免析构过程中还有事件回调进来
    pollTimer->stop();
    if (client->state() != QModbusDevice::UnconnectedState) {
        client->disconnectDevice();
    }
}

ModbusManager *ModbusManager::instance()
{
    static ModbusManager inst;
    return &inst;
}

void ModbusManager::onStateChanged(QModbusDevice::State st) {
    QString message;

    waiting = false;
    switch(st) {
        case QModbusDevice::ConnectedState:
            message = "Modbus TCP 已连接"; break;
        case QModbusDevice::ConnectingState:
            message = "Modbus TCP 连接中"; break;
        case QModbusDevice::ClosingState:
            message = "Modbus TCP 已断开"; break;
        default:
            message = "Modbus TCP 未连接"; break;
    }

    if (st != QModbusDevice::ConnectingState)
        emit logMessage(message);
    emit connectionChanaged(st);
}

void ModbusManager::setConfig(const ProjectConfig &cfg)
{
    // 清空原有轮询列表
    clusters.clear();
    // 筛选启用的电池簇（停用设备不进轮询，也不参与越限监视）
    for (const auto &it : cfg.clusters)
    {
        if (it.enabled)
        {
            clusters.append(it);
        }
    }
    // 更新PCS从站号（0 = 不轮询PCS）
    pcsSlave = cfg.pcsSlave;
    // 轮询游标重置到第一个设备
    pollIndex = 0;
    // 清除历史告警状态、在线状态，重新建立状态机
    alarmState.clear();
    onlineState.clear();

    // 通知UI配置生效，回传启用的簇列表（调试页据此重建实时表）
    emit configApplied(clusters);

    QString pcsTip = (pcsSlave > 0) ? QStringLiteral("PCS(从站%1)").arg(pcsSlave)
                                      : QStringLiteral("无 PCS");
    emit logMessage(QStringLiteral("配置已下发：启用 %1/%2 簇 + %3")
                        .arg(clusters.size())
                        .arg(cfg.clusters.size())
                        .arg(pcsTip));
}

bool ModbusManager::isConnected() {
    return client->state() == QModbusDevice::ConnectedState;
}

void ModbusManager::disconnectDevice()
{
    client->disconnectDevice();
    pollTimer->disconnect();
    waiting = false;
}

void ModbusManager::pollTick()
{
    if (waiting || !isConnected() || (clusters.isEmpty() && pcsSlave <= 0))
        return;


    int total = clusters.size() + (pcsSlave > 0 ? 1 : 0);   // 总设备数，用于游标取模
    bool isPcs = (pollIndex >= clusters.size());            // 游标越过簇列表 = 轮到PCS
    ClusterItem item;                                       // 电池簇时有效，PCS时仅用于离线日志
    int slaveId = pcsSlave;
    if (!isPcs) {
        item = clusters.at(pollIndex);
        slaveId = item.slaveId;
    }
    pollIndex = (pollIndex + 1) % qMax(total, 1);
    auto *reply = client->sendReadRequest(
        QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                        ModbusMap::RegBase, ModbusMap::RegCount),
                        slaveId);

    waiting = true;
    connect(reply, &QModbusReply::finished, this,
            [this, reply, item, isPcs] {
                handlePollReply(reply, item, isPcs);
            });
}

void ModbusManager::handlePollReply(QModbusReply* reply, ClusterItem item, bool isPcs) {
    waiting = false;

    if (reply->error() == QModbusDevice::NoError)
    {
        // 无错误，取出寄存器结果
        QModbusDataUnit unit = reply->result();
        // 寄存器取值lambda，简化代码
        auto reg = [&unit](int off) { return unit.value(off); };

        if (isPcs)
        {
            // ========== PCS数据解析 ==========
            // 偏移常量见 modbusmap.h 的 PcsMap；有符号量（功率、电流、温度）
            // 必须强转 qint16 —— 寄存器是无符号 16 位，直接用会得到 32768 之类的假值
            PcsData d;
            d.power      = qint16(reg(PcsMap::OffPower));    // 0.1kW，正=放电
            d.acVoltage  = reg(PcsMap::OffAcVoltage);        // 0.1V
            d.freq       = reg(PcsMap::OffFreq);             // 0.01Hz
            d.dcVoltage  = reg(PcsMap::OffDcVoltage);        // 0.1V
            d.dcCurrent  = qint16(reg(PcsMap::OffDcCurrent)); // 0.1A，正=充电
            d.temp       = qint16(reg(PcsMap::OffTemp));    // 1°C
            d.statusWord = reg(PcsMap::OffStatus);           // 位定义见 decodePcsStatus
            d.dayChg     = reg(PcsMap::OffDayChg);           // 0.1kWh
            d.dayDis     = reg(PcsMap::OffDayDis);           // 0.1kWh
            d.totalChg   = reg(PcsMap::OffTotalChg);         // 0.1kWh
            d.totalDis   = reg(PcsMap::OffTotalDis);         // 0.1kWh
            // 推送PCS数据更新信号
            emit pcsUpdated(d);
        }
        else
        {
            // ========== 电池簇数据解析 ==========
            ClusterData d;
            d.deviceId   = item.deviceId;   // 主键，界面靠它定位表格行
            d.slaveId    = item.slaveId;
            d.name       = item.name;
            d.voltage    = reg(ModbusMap::OffVoltage);        // 0.1V，无符号
            d.current    = qint16(reg(ModbusMap::OffCurrent)); // 0.1A，负数=放电
            d.soc        = reg(ModbusMap::OffSoc);            // 1%
            d.soh        = reg(ModbusMap::OffSoh);            // 1%
            d.maxTemp    = qint16(reg(ModbusMap::OffMaxTemp)); // 1°C，可为负
            d.minTemp    = qint16(reg(ModbusMap::OffMinTemp));
            d.maxCellV   = reg(ModbusMap::OffMaxCellV);       // mV
            d.minCellV   = reg(ModbusMap::OffMinCellV);       // mV
            d.statusWord = reg(ModbusMap::OffStatus);         // bit0运行 bit1充电 bit2放电 bit3告警 bit4故障

            // 电压原始值是0.1V，除以10得到V，送入越限判断
            // （定值在组态里配的就是V单位，必须先把原始值换算成同一单位再比）
            d.alarmFlags = checkLimits(item.alarm, d.voltage / 10.0, d.maxTemp);

            // ===== 告警边沿检测：掩码没变不打日志；新置位=告警，被清除=恢复 =====
            quint16 prevAlarm = alarmState.value(item.deviceId);
            if (prevAlarm != d.alarmFlags)
            {
                quint16 risen  = d.alarmFlags & ~prevAlarm;   // 新增的告警位
                quint16 fallen = prevAlarm & ~d.alarmFlags;   // 恢复的告警位
                if (risen)
                {
                    emit logMessage(QStringLiteral("%1(从站%2) 越限告警：%3")
                                        .arg(item.name).arg(item.slaveId).arg(AlarmBits::text(risen)));
                }
                if (fallen)
                {
                    emit logMessage(QStringLiteral("%1(从站%2) 告警恢复：%3")
                                        .arg(item.name).arg(item.slaveId).arg(AlarmBits::text(fallen)));
                }
            }
            // 保存当前告警状态
            alarmState.insert(item.deviceId, d.alarmFlags);

            // 如果上一次是离线，现在收到报文，触发【通讯恢复】事件
            if (!onlineState.value(item.deviceId, true))
            {
                onlineState.insert(item.deviceId, true);
                //emit clusterOnline(item.deviceId);
                emit logMessage(QStringLiteral("%1(从站%2) 通讯恢复").arg(item.name).arg(item.slaveId));
            }
            // 推送簇实时数据
            emit clusterUpdated(d);
        }
    }
    else
    {
        // 应答报错：超时或者其他Modbus异常
        // 超时单独给一句人话，剩下的透传 Qt 的错误描述
        QString err;
        if (reply->error() == QModbusDevice::TimeoutError)
        {
            err = QStringLiteral("请求超时，从站无响应");
        }
        else
        {
            err = reply->errorString();
        }
        // 只有电池簇维护离线状态，PCS不处理离线
        if (!isPcs)
        {
            //reportOffline(item, err);
        }

        qDebug() << err;
    }
    // 应答对象销毁：成功失败都要释放，deleteLater 会在事件循环空闲时安全删除
    reply->deleteLater();

}

void ModbusManager::connectTo(const QString &host, int port)
{
    // 重连场景：先把旧链路断干净，否则 setConnectionParameter 不生效
    if (isConnected())
    {
        client->disconnectDevice();
    }

    // 设置连接参数
    client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, host);
    client->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    // 应答超时500ms，重试次数1次
    client->setTimeout(500);
    client->setNumberOfRetries(1);

    emit logMessage(QStringLiteral("正在连接 %1:%2 ...").arg(host).arg(port));
    // 异步发起连接，结果走 stateChanged → onStateChanged 通知
    client->connectDevice();

    // 启动轮询定时器（pollTick 内部会检查连接状态，链路没通时一包也不发）
    if (!pollTimer->isActive())
    {
        pollTimer->start();
    }
}

quint16 ModbusManager::checkLimits(const ClusterAlarm &alarm, double voltV, int maxTemp)
{
    quint16 f = 0;
    // 过压：故障优先级高于预警
    if (voltV >= alarm.ovFault)
    {
        f |= AlarmBits::OvFault;
    }
    else if (voltV >= alarm.ovWarn)
    {
        f |= AlarmBits::OvWarn;
    }

    // 欠压：方向和过压相反，故障优先级高于预警
    if (voltV <= alarm.uvFault)
    {
        f |= AlarmBits::UvFault;
    }
    else if (voltV <= alarm.uvWarn)
    {
        f |= AlarmBits::UvWarn;
    }

    // 过温：故障优先级高于预警
    if (maxTemp >= alarm.otFault)
    {
        f |= AlarmBits::OtFault;
    }
    else if (maxTemp >= alarm.otWarn)
    {
        f |= AlarmBits::OtWarn;
    }

    // 低温：方向和过温相反
    if (maxTemp <= alarm.ltFault)
    {
        f |= AlarmBits::LtFault;
    }
    else if (maxTemp <= alarm.ltWarn)
    {
        f |= AlarmBits::LtWarn;
    }
    return f;
}