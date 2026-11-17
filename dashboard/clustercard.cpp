#include "clustercard.h"
#include "ui_clustercard.h"
// 状态配色：在线绿 / 告警红 / 离线灰，和 KPI 卡的配色口径一致
static const char *kColorOnline  = "#0d9488";
static const char *kColorAlarm   = "#dc2626";
static const char *kColorOffline = "#94a3b8";

ClusterCard::ClusterCard(const ClusterItem &item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusterCard),
    m_slaveId(item.slaveId)
{
    ui->setupUi(this);


    // 让 qss 里 QWidget[class="clusterCard"] 的背景/边框生效（纯 QWidget 子类必须手动开）
    setAttribute(Qt::WA_StyledBackground, true);
    setMinimumSize(180, 112);

    // 名称、从站号只在构造时写死；组态改名要重启才跟着变（和通讯层同一口径）
    ui->cardName->setText(item.name);
    ui->cardStatus->setText(QStringLiteral("离线（从站%1）").arg(m_slaveId));
}

ClusterCard::~ClusterCard()
{
    delete ui;
}

void ClusterCard::setData(const ClusterData &d, bool hasData, bool online)
{
    // 状态行优先级：告警 > 在线 > 离线，谁成立显示谁
    // 告警判定和 KPI 卡4 相同：越限标志 或 BMS 状态字 bit3 任一成立
    const bool alarm = hasData
                       && (d.alarmFlags != 0 || (d.statusWord & 0x08) != 0);

    const char *color = kColorOffline;
    QString status = QStringLiteral("离线（从站%1）").arg(m_slaveId);
    if (alarm)
    {
        color  = kColorAlarm;
        status = QStringLiteral("告警（从站%1）").arg(m_slaveId);
    }
    else if (online)
    {
        color  = kColorOnline;
        status = QStringLiteral("在线（从站%1）").arg(m_slaveId);
    }

    // 圆点和状态文字一起变色，一眼区分三种状态
    ui->dot->setStyleSheet(QStringLiteral("color:%1;").arg(color));
    ui->cardStatus->setStyleSheet(QStringLiteral("color:%1;").arg(color));
    ui->cardStatus->setText(status);

    // 从没收到过数据：数字区保持 designer 里的 "--" 默认值
    if (!hasData)
        return;

    // 原始值是 0.1V / 0.1A / mV，这里按工程量换算显示
    ui->cardSoc->setText(QStringLiteral("%1 %").arg(d.soc));
    ui->cardVolt->setText(QStringLiteral("簇电压 %1 V").arg(d.voltage / 10.0, 0, 'f', 1));
    ui->cardTemp->setText(QStringLiteral("温度 %1 °C").arg(d.maxTemp));
    ui->cardFoot->setText(QStringLiteral("单体压差 %1 mV · SOH %2 %")
                              .arg(d.maxCellV - d.minCellV).arg(d.soh));
}
