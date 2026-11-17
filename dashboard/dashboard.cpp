#include "dashboard.h"
#include "ui_dashboard.h"
#include <QFile>

// 超过这么多秒没收到新数据，就当这一簇离线。
static const int kOfflineSecs = 15;

DashBoard::DashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoard)
{
    ui->setupUi(this);
    QFile qss(":/style/dashboard.qss");
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text))
        this->setStyleSheet(QString::fromUtf8(qss.readAll()));

    ProjectConfig *cfg = ProjectConfig::instance();
    if (cfg->clusters.isEmpty())
    {
        cfg->setFilePath(QCoreApplication::applicationDirPath() + "/project_config.json");
        cfg->loadFromFile();
    }

    //要设置的kpi卡片数据label 存放到链表里面
    m_valueLabels = { ui->lblKpiValue0, ui->lblKpiValue1, ui->lblKpiValue2,
                     ui->lblKpiValue3, ui->lblKpiValue4 };
    m_subLabels   = { ui->lblKpiSub0, ui->lblKpiSub1, ui->lblKpiSub2,
                   ui->lblKpiSub3, ui->lblKpiSub4 };

    ModbusManager* mode =  ModbusManager::instance();
    //当连接上数据服务器 同步接收数据
    connect(mode,&ModbusManager::connectionChanaged,this,&DashBoard::onConnectionState);
    connect(mode,&ModbusManager::clusterUpdated,this,&DashBoard::onClusterUpdate);
    connect(mode,&ModbusManager::pcsUpdated,this,&DashBoard::onPcsUpdate);

    buildClusterWall();
    //自己创建一个定时器,刷新我自己的界面
    this->timer= new QTimer(this);
    this->timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,&DashBoard::refreshKpi);
    this->timer->start();//启动定时器
    //刷新界面
    refreshKpi();
    //初始化结束以后--构建卡片墙


}

DashBoard::~DashBoard()
{
    delete ui;
}

void DashBoard::setKpi(int index, const QString &kpiVal, const QString &subVal, bool warm)
{
    if (index < 0 || index >= m_valueLabels.size())
        return;

    m_valueLabels[index]->setText(kpiVal);
    m_subLabels[index]->setText(subVal);

    m_valueLabels[index]->setStyleSheet(
        warm? QStringLiteral("font-size: 22px; font-weight: 700; color: #dc2626;")
             :
            QStringLiteral("font-size: 22px; font-weight: 700; color: #0f172a;")
        );
}

void DashBoard::buildClusterWall()
{
    //总列数 3
    const int totalCol=3;
    //用来累加电池电芯的数量
    int totalCells =0;
    //定义两个变量 计算每一个卡片所在的位置
    int row=0,col=0;
    //获取内存里面 有多少个电池簇
    QList<ClusterItem> lists =  ProjectConfig::instance()->clusters;
    //每一个启用的 ClusterItem 制作一个卡片
    for(ClusterItem item :lists){
        if (!item.enabled)
            continue;
        ClusterCard *card =  new ClusterCard(item,this);
        ui->wallGrid->addWidget(card,row,col);

        m_cards.append(card);
        m_cardIds.append(item.deviceId);
        //累加电芯数量
        totalCells+=item.cellSerial;

        if (++col == totalCol)
        {
            col = 0;
            ++row;
        }
    }

    //处理页面的标题
    // 标题带上规模，例：电池簇运行状态（5 簇 / 1040 串）
    const int count = m_cards.size();
    if (count > 0)
        ui->lblWallTitle->setText(QStringLiteral("电池簇运行状态（%1 簇 / %2 串）")
                                      .arg(count).arg(totalCells));
    else
        ui->lblWallTitle->setText(QStringLiteral("电池簇运行状态（未配置电池簇）"));

}

void DashBoard::onPcsUpdate(const PcsData &data)
{
    this->m_pcs = data;
    m_hasPcs=true;
}

void DashBoard::onClusterUpdate(const ClusterData &data)
{
    this->m_clusters.insert(data.deviceId,data);
    this->m_stam.insert(data.deviceId,QDateTime::currentDateTime());
}

void DashBoard::onConnectionState(bool onLine)
{
    this->m_connected= onLine;
}

void DashBoard::refreshKpi()
{
    const QDateTime now = QDateTime::currentDateTime();
    //为了后面算总SOC 做准备
    QHash<int , double> capById;
    int capTotal=0;
    //算配置文件里面的总容量
    const QList<ClusterItem> &lists=  ProjectConfig::instance()->clusters;
    for(auto item : lists){
        if(!item.enabled)continue;
        capById.insert(item.deviceId,item.ratedCapacity);
        capTotal+=item.ratedCapacity;
    }

    // 一次遍历，把后面要用的统计量全算出来
    int    count    = 0;     // 收到过数据的簇数
    int    online   = 0;     // kOfflineSecs 秒内有新数据的簇数
    int    alarm    = 0;     // 有告警的簇数
    int    socSum   = 0;
    int    tempSum  = 0;
    int    tempMax  = -999;  // 最高温度，取一个不可能的值做初值
    double capAvail = 0;     // 可用电量 Σ(SOC × 额定容量)

    for (auto it = m_clusters.constBegin(); it != m_clusters.constEnd(); ++it)
    {
        const ClusterData &d = it.value();
        ++count;
        socSum  += d.soc;
        tempSum += d.maxTemp;
        if (d.maxTemp > tempMax)
            tempMax = d.maxTemp;
        capAvail += d.soc / 100.0 * capById.value(it.key());

        const QDateTime stamp = m_stam.value(it.key());

        if (stamp.isValid() && stamp.secsTo(now) <= kOfflineSecs)
            ++online;

        // 告警有两个来源，任一成立就算：
        //   1) alarmFlags：上位机按总压/最高温自己判的越限；
        //   2) statusWord bit3：BMS 自己报的告警（单体过温、绝缘等本地点表看不出来的故障）
        const bool selfAlarm = (d.statusWord & 0x08) != 0;
        if (d.alarmFlags != 0 || selfAlarm)
            ++alarm;
    }
    //向页面填充数据
    if(count>0){
        setKpi(0, QStringLiteral("%1 %").arg(socSum / double(count), 0, 'f', 1),
               QStringLiteral("可用 %1 / %2 kWh").arg(capAvail, 0, 'f', 0).arg((double)capTotal,0,'f', 0));
    }else{
        setKpi(0, QStringLiteral("--"),
               m_connected ? QStringLiteral("等待数据") : QStringLiteral("未连接"));
    }

    // 卡1 当前功率：PCS 上报，正=放电 负=充电，副标题给方向 + 能量效率
    // 效率口径：日放电 / 日充电（累计电量的比值），充电量为 0 时先不显示
    if (m_hasPcs)
    {
        const double kw = m_pcs.power / 10.0;
        const QString dir = (kw > 0.1)  ? QStringLiteral("放电中")
                            : (kw < -0.1) ? QStringLiteral("充电中")
                                          : QStringLiteral("待机");
        QString sub = dir;
        if (m_pcs.dayChg > 0)
        {
            sub = QStringLiteral("%1 · 效率 %2%")
                      .arg(dir)
                      .arg(m_pcs.dayDis * 100.0 / m_pcs.dayChg, 0, 'f', 1);
        }
        setKpi(1, QStringLiteral("%1 kW").arg(qAbs(kw), 0, 'f', 1), sub);
    }
    else
    {
        setKpi(1, QStringLiteral("--"), QStringLiteral("PCS 未配置"));
    }

    // 卡2 今日充电量：值取日充电量，副标题补日放电量
    if (m_hasPcs)
    {
        setKpi(2, QStringLiteral("%1 kWh").arg(m_pcs.dayChg / 10.0, 0, 'f', 1),
               QStringLiteral("放电 %1 kWh").arg(m_pcs.dayDis / 10.0, 0, 'f', 1));
    }
    else
    {
        setKpi(2, QStringLiteral("--"), QStringLiteral("PCS 未配置"));
    }
    // 卡3 平均温度：各簇最高温的平均，副标题给出全场最高；有告警追加红字提示
    if (count > 0)
    {
        QString sub = QStringLiteral("最高 %1 °C").arg(double(tempMax), 0, 'f', 1);
        if (alarm > 0)
            sub += QStringLiteral(" · <span style='color:#dc2626;'>告警</span>");
        setKpi(3, QStringLiteral("%1 °C").arg(tempSum / double(count), 0, 'f', 1), sub);
    }
    else
    {
        setKpi(3, QStringLiteral("--"),
               m_connected ? QStringLiteral("等待数据") : QStringLiteral("未连接"));
    }

    // 卡4 在线 / 告警：在线簇数 / 告警簇数，告警数字单独标红
    const int total = enabledClusterCount();
    if (total > 0)
    {
        // 有告警时只把告警数标红（QLabel 支持简单富文本）
        QString value;
        if (alarm > 0)
            value = QStringLiteral("%1/<span style='color:#dc2626;'>%2</span>")
                        .arg(online).arg(alarm);
        else
            value = QStringLiteral("%1/%2").arg(online).arg(alarm);

        const QString sub = (online >= total)
                                ? QStringLiteral("全部在线")
                                : QStringLiteral("离线 %1 台").arg(total - online);
        setKpi(4, value, sub);
    }
    else
    {
        setKpi(4, QStringLiteral("--"), QStringLiteral("未配置设备"));
    }


    // 逐张刷新簇卡片：查缓存 + 判在线，交给卡片自己更新文字和颜色

    for (int i = 0; i < m_cards.size(); ++i)
    {
        const int id = m_cardIds.at(i);
        const bool hasData = m_clusters.contains(id);
        const ClusterData d = m_clusters.value(id);
        const QDateTime stamp = m_stam.value(id);
        const bool online = hasData && stamp.isValid()
                            && stamp.secsTo(now) <= kOfflineSecs;
        m_cards.at(i)->setData(d, hasData, online);
    }


}
// ---------------------- 启用的簇数量 ----------------------
int DashBoard::enabledClusterCount() const
{
    int n = 0;
    const QList<ClusterItem> &list = ProjectConfig::instance()->clusters;
    for (const ClusterItem &item : list)
    {
        if (item.enabled)
            ++n;
    }
    return n;
}
