#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QWidget>
#include "device/projectconfig.h"

namespace Ui {
class DeviceConfig;
}

class DeviceConfig : public QWidget
{
    Q_OBJECT

private:
    void refreshTable();
    void fillRow(int row, ClusterItem& item);
public:
    explicit DeviceConfig(QWidget *parent = nullptr);
    ~DeviceConfig();

private:
    Ui::DeviceConfig *ui;
};

#endif // DEVICECONFIG_H
