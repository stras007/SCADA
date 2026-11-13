#include "device/deviceconfig.h"
#include "ui_deviceconfig.h"


DeviceConfig::DeviceConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceConfig)
{
    ui->setupUi(this);

    // 配置
    ProjectConfig* config = ProjectConfig::instance();
    config->setFilePath(QCoreApplication::applicationDirPath() + "/project_config.json");

    // load
    config->loadFromFile();

    // refresh table
    refreshTable();
    qDebug() << config->nextDeviceId;
}

DeviceConfig::~DeviceConfig()
{
    delete ui;
}


void DeviceConfig::fillRow(int row, ClusterItem& c){
    // 第0列：设备ID
    ui->deviceTable->setItem(row, 0, new QTableWidgetItem(QString::number(c.deviceId)));
    // 第1列：簇名称
    ui->deviceTable->setItem(row, 1, new QTableWidgetItem(c.name));
    // 第2列：设备型号
    ui->deviceTable->setItem(row, 2, new QTableWidgetItem(c.model));
    // 第3列：所属PCS单元
    ui->deviceTable->setItem(row, 3, new QTableWidgetItem(QString("单元%1").arg(c.pcsUnit)));
    // 第4列：Modbus从站号
    ui->deviceTable->setItem(row, 4, new QTableWidgetItem(QString::number(c.slaveId)));
    // 第5列：额定电压，保留1位小数
    ui->deviceTable->setItem(row, 5, new QTableWidgetItem(QString::number(c.ratedVoltage, 'f', 1)));
    // 第6列：额定容量，保留1位小数
    ui->deviceTable->setItem(row, 6, new QTableWidgetItem(QString::number(c.ratedCapacity, 'f', 1)));

    ui->deviceTable->setItem(row, 7, new QTableWidgetItem(c.enabled ? "启用" : "停用"));


    // 如果设备是停用状态，把这一行所有文字改成灰色；启用为黑色
    QColor textColor;
    if (c.enabled)
    {
        textColor = QColor(0x0f172a); // 正常黑色文字
    }
    else
    {
        textColor = QColor(0x94a3b8); // 灰色
    }

    // 设置文字颜色
    for (int col = 0; col < 8; col++)
    {
        QTableWidgetItem* item = ui->deviceTable->item(row, col);
        item->setForeground(textColor);
    }
}

void DeviceConfig::refreshTable() {
    // 取出电池簇
    ProjectConfig *config = ProjectConfig::instance();
    QList<ClusterItem> list = config->clusters;

    // 设置行数，并渲染每行
    ui->deviceTable->setRowCount(list.size());
    for (int i = 0;i < list.size(); i ++ ) {
        fillRow(i, list[i]);
    }

    ui->spinPcsSlave->setValue(config->pcsSlave);
}