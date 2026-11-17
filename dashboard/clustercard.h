#ifndef CLUSTERCARD_H
#define CLUSTERCARD_H

#include <QWidget>
#include "projectconfig.h"
#include "modbusmanager.h"

namespace Ui {
class ClusterCard;
}

class ClusterCard : public QWidget
{
    Q_OBJECT

public:
    explicit ClusterCard(const ClusterItem &item, QWidget *parent = nullptr);
    ~ClusterCard();
    void setData(const ClusterData &d, bool hasData, bool online);

private:
    Ui::ClusterCard *ui;

    int m_slaveId;
};

#endif // CLUSTERCARD_H
