#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QWidget>

namespace Ui {
class DeviceConfig;
}

class DeviceConfig : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceConfig(QWidget *parent = nullptr);
    ~DeviceConfig();

private:
    Ui::DeviceConfig *ui;
};

#endif // DEVICECONFIG_H
