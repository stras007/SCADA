#include "deviceconfig.h"
#include "ui_deviceconfig.h"

DeviceConfig::DeviceConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceConfig)
{
    ui->setupUi(this);
}

DeviceConfig::~DeviceConfig()
{
    delete ui;
}
