#include "deviceconfig.h"
#include "ui_deviceconfig.h"
#include "dialog.h"
#include <QMessageBox>
#include <QDebug>

DeviceConfig::DeviceConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceConfig)
{
    ui->setupUi(this);

    QFile qss(QStringLiteral(":/style/deviceconfig.qss"));
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(qss.readAll()));
        qss.close();
    }

    // 配置project_json并load
    config->setFilePath(QCoreApplication::applicationDirPath() + "/project_config.json");
    config->loadFromFile();

    // refresh table
    refreshTable();

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
    QList<ClusterItem> list = config->clusters;

    // 设置行数，并渲染每行
    ui->deviceTable->setRowCount(list.size());
    for (int i = 0;i < list.size(); i ++ ) {
        fillRow(i, list[i]);
    }

    ui->spinPcsSlave->setValue(config->pcsSlave);
}
void DeviceConfig::on_btnAddDevice_clicked()
{
    // --------------------------
    // 1. 查找clusters中最小未占用deviceId，更新nextDeviceId
    // --------------------------
    QSet<int> existDevIds;
    for(const auto &item : config->clusters)
        existDevIds.insert(item.deviceId);

    int minFreeDevId = 1;
    while(existDevIds.contains(minFreeDevId))
        minFreeDevId++;

    // 更新单例nextDeviceId为最小可用ID
    config->nextDeviceId = minFreeDevId;

    // --------------------------
    // 2. 搜寻最小空闲Modbus从站地址（1-247），PCS从站号也算占用
    // --------------------------
    QSet<int> usedSlave;
    for(const auto &item : config->clusters)
        usedSlave.insert(item.slaveId);

    if(config->pcsSlave > 0)
        usedSlave.insert(config->pcsSlave);

    int freeSlave = 1;
    for(; freeSlave <= 247; freeSlave++)
        if(!usedSlave.contains(freeSlave)) break;


    // --------------------------
    // 3.构造预填的新簇对象，默认【停用】
    // --------------------------
    ClusterItem newItem;
    newItem.deviceId = config->nextDeviceId;
    newItem.slaveId = freeSlave;
    newItem.name = QStringLiteral("电池簇%1").arg(newItem.deviceId);
    newItem.enabled = false; // 新增默认不启用采集

    // --------------------------
    // 4.打开弹窗，填充全部默认值
    // --------------------------
    Dialog dlg(this); dlg.setConfig(newItem);

    int ret = dlg.exec();
    // 用户点取消，直接返回，内存不做任何修改
    if(ret != QDialog::Accepted)
        return;


    // --------------------------
    // 5.用户点击确定：写入单例内存，暂时不写磁盘文件
    // --------------------------
    ClusterItem finalItem = dlg.config();
    config->clusters.append(finalItem);

    // UI表格新增一行
    int newRow = config->clusters.size() - 1;
    ui->deviceTable->insertRow(newRow);
    fillRow(newRow, config->clusters.last());
}


void DeviceConfig::on_btnEditDevice_clicked()
{
    auto* table = ui->deviceTable;

    // 1. 判断是否选中行
    QList<QTableWidgetItem*> selectItems = table->selectedItems();
    if (selectItems.isEmpty())
    {
        QMessageBox::warning(this, tr("提示"), tr("请先选择要编辑的设备行！"));
        return;
    }

    auto ranges = table->selectedRanges();
    if(ranges.size() > 1)
    {
        QMessageBox::warning(this, tr("提示"), tr("一次只能编辑一行设备！"));
        return;
    }

    // 获取选中的行号（取第一个选中项的行）
    int selectedRow = selectItems.first()->row();

    // 校验行号合法
    if (selectedRow < 0 || selectedRow >= config->clusters.size())
    {
        QMessageBox::warning(this, tr("提示"), tr("选中行无效"));
        return;
    }

    // 取出内存中原始数据
    ClusterItem editItem = config->clusters.at(selectedRow);

    // 打开编辑弹窗，填充原有数据
    Dialog dlg(this); dlg.setConfig(editItem);

    int ret = dlg.exec();
    if (ret != QDialog::Accepted)
    {
        // 用户点击取消，什么都不做直接返回
        return;
    }

    // 用户点击确定：拿到弹窗修改后的结构体，回写到内存对应位置
    ClusterItem modifiedItem = dlg.config();

    // 重要：deviceId不允许编辑，强制还原原始deviceId
    //（弹窗里label只展示不可改，但读回时保险起见再还原一次）
    modifiedItem.deviceId = editItem.deviceId;

    // 覆盖内存里面对应位置
    config->clusters[selectedRow] = modifiedItem;

    // 刷新表格这一行
    fillRow(selectedRow, config->clusters[selectedRow]);
}


void DeviceConfig::on_btnRemoveDevice_clicked()
{
    auto* table = ui->deviceTable;

    // 1. 从选中区域提取行号，并去重（同一行被多个格子覆盖时只算一次）
    QSet<int> rowSet;
    for (const QTableWidgetSelectionRange& r : table->selectedRanges())
        for (int i = r.topRow(); i <= r.bottomRow(); ++i)
            rowSet.insert(i);

    if (rowSet.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("请先选择要删除的设备行！"));
        return;
    }

    // 2. 降序排列：从大行号往小删，避免删除后后面的行号整体上移
    QList<int> rows = rowSet.values();
    std::sort(rows.begin(), rows.end(), std::greater<int>());

    // 3. 先做一次性的校验和确认，不要放在循环里
    QStringList names;
    for (int row : rows)
        if (row >= 0 && row < config->clusters.size())
            names << config->clusters.at(row).name;

    if (names.isEmpty()) return;

    int ret = QMessageBox::question(this, tr("确认删除"),
                                    tr("确定要删除以下 %1 台设备吗？\n%2\n删除后需要点击保存才会更新配置文件。")
                                        .arg(names.size()).arg(names.join("、")),
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret != QMessageBox::Yes) return;

    // 4. 统一删除，内存和表格同步进行
    for (int row : rows) {
        config->clusters.removeAt(row);
        ui->deviceTable->removeRow(row);
    }
}



void DeviceConfig::on_btnRevert_clicked()
{
    int ret = QMessageBox::question(this, tr("确认还原"),
                                    tr("将会丢弃所有未保存修改，重新从配置文件加载数据，是否继续？"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes)
    {
        return;
    }

    // 从磁盘json文件重新加载，覆盖当前全部内存数据
    bool loadOk = config->loadFromFile();
    if (!loadOk)
    {
        QMessageBox::warning(this, tr("错误"), tr("还原失败，读取配置文件出错！"));
        return;
    }

    // 刷新整个表格UI，显示磁盘里最新的数据
    refreshTable();

    QMessageBox::information(this, tr("提示"), tr("已还原为配置文件中的内容"));
}


void DeviceConfig::on_btnApply_clicked()
{

    // 把页面上修改的PCS从站号先写回内存，再一起落盘
    config->pcsSlave = ui->spinPcsSlave->value();

    // 将单例内存全部数据覆盖写入磁盘json文件
    bool saveResult = config->saveToFile();
    if (!saveResult)
    {
        QMessageBox::warning(this, tr("错误"), tr("下发配置失败，写入配置文件出错！"));
        return;
    }

    QMessageBox::information(this, tr("成功"), tr("配置已保存到文件！"));
}
