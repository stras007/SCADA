#ifndef MODBUSDEBUG_H
#define MODBUSDEBUG_H

#include <QMainWindow>
#include "device/projectconfig.h"
#include "common/modbusmanager.h"

namespace Ui {
class ModbusDebug;
}

class ModbusDebug : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModbusDebug(QMainWindow *parent = nullptr);
    ~ModbusDebug();

private slots:
    void on_btnConnect_clicked();
    void onLog(const QString &msg);
    void onClusterUpdated(const ClusterData& data);
    void onPcsUpdated(const PcsData& data);
    void setCellText(int row, int col, const QString &text);
    void setRowColor(int row, const QColor &color);
    int findDataRow(int deviceId) const;

private:
    Ui::ModbusDebug *ui;
    ProjectConfig *config = ProjectConfig::instance();
    ModbusManager *mmanger = ModbusManager::instance();
    void onModbusConnectionChanged(QModbusDevice::State st);
    QModbusDevice::State mst; // 连接状态
};

#endif // MODBUSDEBUG_H
