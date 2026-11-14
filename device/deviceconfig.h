#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QWidget>
#include "projectconfig.h"

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

private slots:
    void on_btnAddDevice_clicked();

    void on_btnEditDevice_clicked();

    void on_btnRemoveDevice_clicked();

    void on_btnRevert_clicked();

    void on_btnApply_clicked();

private:
    Ui::DeviceConfig *ui;
    ProjectConfig *config = ProjectConfig::instance();
};

#endif // DEVICECONFIG_H
