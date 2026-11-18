#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "modbusmanager.h"
#include "projectconfig.h"
#include <QHash>
#include <QLabel>
#include "clustercard.h"
#include <QBarSet>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>


namespace Ui {
class DashBoard;
}

class DashBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashBoard(QWidget *parent = nullptr);
    ~DashBoard();
    void  setKpi(int index, const QString &kpiVal,const QString &subVal,bool warm=false);
    void buildClusterWall();
    //初始化界面 soc柱状图的页面样式
    void initSocChart();
    void initTrendChart();//统计近10分钟soc 功率
    void refreshCharts(const QDateTime &now);//刷新数据

private slots:
    void onPcsUpdate(const PcsData &data);
    void onClusterUpdate(const ClusterData &data);
    void onConnectionState(bool onLine);
    void refreshKpi();

    int enabledClusterCount() const ;   // 重算并刷新 5 张卡片;
private:
    Ui::DashBoard *ui;

    bool m_hasPcs =false;//默认没有pcs数据
    QHash<int , ClusterData> m_clusters;
    QHash<int , QDateTime> m_stam;
    bool    m_connected = false;
    PcsData m_pcs;

    QTimer* timer;

    QList<QLabel*> m_valueLabels;
    QList<QLabel*> m_subLabels;

    QList<ClusterCard*> m_cards;          // 簇状态卡片，铺墙顺序即显示顺序
    QList<int> m_cardIds;                 // m_cards 下标对应的 deviceId，刷新时查数据用

    // ---- 图表骨架：这里存的是构造时建好的对象，之后只换数据，不重建 ----
    QLineSeries   *m_powerSeries = nullptr;  // 功率趋势的折线序列
    QLineSeries   *m_socLine     = nullptr;  // SOC 趋势的折线序列（双纵轴的右轴）
    QDateTimeAxis *m_trendX      = nullptr;  // 时间轴，两条线共用，窗口随当前时间滚动
    QValueAxis    *m_trendY      = nullptr;  // 左轴：功率，对称量程
    QValueAxis    *m_socY        = nullptr;  // 右轴：SOC，固定 0~100


    QBarSet *m_socSet;
    double m_powerPeak = 50.0;               // 功率量程峰值：至少 ±50kW，见到更大值再扩
    double m_socAvg    = -1.0;               // 系统 SOC 均值，<0 表示这一秒没有可画的点
};

#endif // DASHBOARD_H
