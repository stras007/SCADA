#include "modbusdebug.h"
#include "ui_modbusdebug.h"
#include <QFile>
#include <QModbusDevice>
#include <QScrollBar>


ModbusDebug::ModbusDebug(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::ModbusDebug)
{
    ui->setupUi(this);
    if (!ui->centralwidget->layout()) {
        auto *lay = new QVBoxLayout(ui->centralwidget);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->setSpacing(0);
        lay->addWidget(ui->scrollAreaPage);
    }

    QFile qss(QStringLiteral(":/style/modbusdebug.qss"));
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(qss.readAll()));
        qss.close();
    }


    connect(mmanger, &ModbusManager::logMessage, this, &ModbusDebug::onLog);
    connect(mmanger, &ModbusManager::connectionChanaged,
            this, &ModbusDebug::onModbusConnectionChanged);

    connect(mmanger, &ModbusManager::pcsUpdated,
            this, &ModbusDebug::onPcsUpdated);

    connect(mmanger, &ModbusManager::clusterUpdated,
            this, &ModbusDebug::onClusterUpdated);


    mmanger->setConfig(*this->config);
    syncRealtimeRows();

    ui->logEdit->setMaximumBlockCount(300);

}
static const QColor kColorNormal (0x0f172a);   // 正常：深色（接近纯黑的蓝灰）
static const QColor kColorOffline(0x94a3b8);   // 离线/未连接：浅灰（暗示数据不可信）
static const QColor kColorAlarm  (0xb91c1c);   // 告警：红（一眼定位问题簇）
static QString decodeStatus(int w)
{
    QStringList s;
    if (w & 0x01) s << "运行";
    if (w & 0x02) s << "充电";
    if (w & 0x04) s << "放电";
    if (w & 0x08) s << "告警";
    if (w & 0x10) s << "故障";
    // 状态字全 0 有两种可能：设备真离线，或刚上电还没置位。
    // 调试页不区分，统一显示"离线"，真实状态看这一行有没有数值。
    return s.isEmpty() ? "离线" : s.join("/");
}

static QString decodePcsStatus(int w)
{
    QStringList s;
    if (w & 0x01) s << "待机";
    if (w & 0x02) s << "并网运行";
    if (w & 0x04) s << "故障";
    if (w & 0x08) s << "限功率";
    return s.isEmpty() ? "离线" : s.join("/");
}

ModbusDebug::~ModbusDebug()
{
    delete ui;
}

void ModbusDebug::on_btnConnect_clicked()
{
    // 如果当前已经处于连接状态，执行断开
    if (mmanger->isConnected())
    {
        mmanger->disconnectDevice();
        // onLog(QStringLiteral("用户主动断开Modbus连接"));
        return;
    }
    // 读取输入框地址端口，去除首尾空白（复制粘贴时容易带空格）
    QString host = ui->editHost->text().trimmed();
    int port = ui->editPort->text().toInt();

    // 简单参数校验（加上日志提示，用户知道为什么失败）
    if (host.isEmpty())
    {
        // onLog(QStringLiteral("【错误】IP地址不能为空！"));
        return;
    }
    if (port <= 0 || port > 65535)
    {
        // onLog(QStringLiteral("【错误】端口号范围必须是 1~65535！"));
        return;
    }
    // 发起Modbus TCP连接（结果由 connectionChanged 信号异步通知回来）
    mmanger->connectTo(host, port);
    // 保存连接参数到工程配置（仅通道参数，不修改设备台账）
    config->port = port;
    config->host = host;
    // onLog(QStringLiteral("发起连接 %1:%2").arg(host).arg(port));
}

void ModbusDebug::onLog(const QString &msg)
{
    ui->logEdit->appendPlainText(
        QStringLiteral("[%1] %2").
        arg(QTime::currentTime().
        toString("hh:mm:ss"), msg));
    QScrollBar *bar = ui->logEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ModbusDebug::setCellText(int row, int col, const QString &text)
{
    QTableWidgetItem *item = ui->realtimeTable->item(row, col);
    if (item)
        item->setText(text);
}

void ModbusDebug::setRowColor(int row, const QColor &color)
{
    for (int c = 0; c < 6; ++c)
        if (auto *it = ui->realtimeTable->item(row, c))
            it->setForeground(QBrush(color));
}

int ModbusDebug::findDataRow(int deviceId) const
{
    for (int r = 0; r < ui->realtimeTable->rowCount(); r++)
    {
        auto* item = ui->realtimeTable->item(r, 0);
        if (item && item->data(Qt::UserRole).toInt() == deviceId)
        {
            return r;
        }
    }
    return -1;
}

void ModbusDebug::syncRealtimeRows()
{
    QList<ClusterItem> list;
    for (auto cluster : config->clusters)
        if (cluster.enabled)
            list.push_back(cluster);

    ui->realtimeTable->setRowCount(list.size());
    for (int row = 0;row < list.size(); row ++ ) {

        for (int col = 0; col < 6; col ++ ) {
            QString text = "-";
            if (col == 0) text = QStringLiteral("%1 (从站%2)").arg(list[row].name).arg(list[row].slaveId);
            ui->realtimeTable->setItem(row, col, new QTableWidgetItem(text));
        }
        ui->realtimeTable->item(row, 0)->setData(Qt::UserRole, list[row].deviceId);
        setRowColor(row, kColorOffline);
    }
}

void ModbusDebug::onClusterUpdated(const ClusterData &d)
{
    // 输出窗口同步打印一份数据，方便不开界面时用命令行看采集节奏
    qDebug().noquote() << QStringLiteral("[%1] %2 从站%3 电压%4V 电流%5A SOC %6% 最高温%7°C")
                              .arg(QTime::currentTime().toString("hh:mm:ss"), d.name).arg(d.slaveId)
                              .arg(d.voltage / 10.0, 0, 'f', 1).arg(d.current / 10.0, 0, 'f', 1)
                              .arg(d.soc).arg(d.maxTemp);

    int row = findDataRow(d.deviceId);

    if (row < 0)
    {
        // 找不到行 = 台账已经切换，报文过期，直接丢弃
        // （下发配置瞬间常见：旧设备的最后一包数据回来时行已经没了）


        return;
    }

    // 0~4列：名称、电压、电流、SOC、最高温
    setCellText(row, 0, QStringLiteral("%1 (从站%2)").arg(d.name).arg(d.slaveId));
    setCellText(row, 1, QStringLiteral("%1 V").arg(d.voltage / 10.0, 0, 'f', 1));
    setCellText(row, 2, QStringLiteral("%1 A").arg(d.current / 10.0, 0, 'f', 1));
    setCellText(row, 3, QStringLiteral("%1 %").arg(d.soc));
    setCellText(row, 4, QStringLiteral("%1 °C").arg(d.maxTemp));

    // 第5列：状态 + 告警拼接。
    // 状态字来自设备上报（bit位见 decodeStatus），告警掩码来自本地越限判断，
    // 两个来源都显示 —— 现场有的 BMS 自己判告警，有的只给原始值
    QString statusText = decodeStatus(d.statusWord);
    if (d.alarmFlags != 0)
        statusText += QStringLiteral(" [%1]").arg(AlarmBits::text(d.alarmFlags));
    setCellText(row, 5, statusText);

    // 告警标红：设备状态字 bit3（告警）或本地越限掩码非 0，任一命中就算告警
    bool isAlarm = ((d.statusWord & 0x08) != 0) || (d.alarmFlags != 0);
    setRowColor(row, isAlarm ? kColorAlarm : kColorNormal);
}


void ModbusDebug::onPcsUpdated(const PcsData &d)
{
    // 输出窗口同步打印一份，便于核对采集节奏
    qDebug().noquote() << QStringLiteral("[%1] PCS 功率%2kW 交流%3V 频率%4Hz 日充%5kWh 日放%6kWh")
                              .arg(QTime::currentTime().toString("hh:mm:ss"))
                              .arg(d.power / 10.0, 0, 'f', 1).arg(d.acVoltage / 10.0, 0, 'f', 1)
                              .arg(d.freq / 100.0, 0, 'f', 2)
                              .arg(d.dayChg / 10.0, 0, 'f', 1).arg(d.dayDis / 10.0, 0, 'f', 1);

    ui->lblPcsPower->setText(QStringLiteral("%1 kW").arg(d.power / 10.0, 0, 'f', 1));
    ui->lblPcsAcV->setText(QStringLiteral("%1 V").arg(d.acVoltage / 10.0, 0, 'f', 1));
    ui->lblPcsFreq->setText(QStringLiteral("%1 Hz").arg(d.freq / 100.0, 0, 'f', 2));
    ui->lblPcsState->setText(decodePcsStatus(d.statusWord));
    ui->lblPcsDayChg->setText(QStringLiteral("%1 kWh").arg(d.dayChg / 10.0, 0, 'f', 1));
    ui->lblPcsDayDis->setText(QStringLiteral("%1 kWh").arg(d.dayDis / 10.0, 0, 'f', 1));
    ui->lblPcsTotalChg->setText(QStringLiteral("%1 kWh").arg(d.totalChg / 10.0, 0, 'f', 1));
    ui->lblPcsTotalDis->setText(QStringLiteral("%1 kWh").arg(d.totalDis / 10.0, 0, 'f', 1));
}



void ModbusDebug::onModbusConnectionChanged(QModbusDevice::State st)
{
    // 缓存全局连接标记：syncRealtimeRows 建新行时用它决定初始状态文字
    mst = st;

    // 更新标签和按钮文字（按钮是"连接/断开"二态切换）
    QString message;
    bool connected = false, connecting = false;
    switch(st) {
        case QModbusDevice::ConnectedState:
            message = "Modbus TCP 已连接"; connected = true; break;
        case QModbusDevice::ConnectingState:
            message = "Modbus TCP 连接中..."; connecting = true; break;
        case QModbusDevice::ClosingState:
            message = "Modbus TCP 已断开"; break;
        default:
            message = "Modbus TCP 未连接"; break;
    }

    ui->lblConnState->setText(message);
    ui->btnConnect->setText(connected ? "断开" : "连接");

    // 设置自定义属性并强制刷新QSS样式
    // 坑：QSS 的属性选择器 [online="true"] 只在 polish 时求值，
    //     只 setProperty 不重新 polish，颜色不会变
    ui->lblConnState->setProperty("online", connected || connecting);
    ui->btnConnect->setEnabled(!connecting);
    ui->lblConnState->style()->unpolish(ui->lblConnState);
    ui->lblConnState->style()->polish(ui->lblConnState);

    // TCP链路断开：表格全部设备置为未连接、整行置灰
    // （连不上链路时轮询本来就不跑，这里不用等超时，立即反映）
    if (!connected)
    {
        for (int r = 0; r < ui->realtimeTable->rowCount(); r ++ )
        {
            setCellText(r, 5, QStringLiteral("未连接"));
            setRowColor(r, kColorOffline);
        }
    }
}