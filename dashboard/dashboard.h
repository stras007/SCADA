#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "modbusmanager.h"
#include "projectconfig.h"
#include <QHash>
#include <QLabel>
#include "clustercard.h"


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
};

#endif // DASHBOARD_H