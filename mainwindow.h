#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusTcpClient>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void onStateChanged(QModbusDevice::State state);
    void onBmsReplyFinished();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    // 按登录角色禁用/放开侧边栏入口，并在状态栏显示当前用户
    void applyRolePermissions();

    Ui::MainWindow *ui;
    QModbusTcpClient *client = nullptr;
};
#endif // MAINWINDOW_H
