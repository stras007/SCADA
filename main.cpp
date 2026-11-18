#include "mainwindow.h"
#include "login/login.h"

#include <QApplication>
#include <QDebug>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSettings 用这两个名字定位注册表/配置目录，必须在第一次 QSettings 之前设置
    QApplication::setOrganizationName(QStringLiteral("stras"));
    QApplication::setApplicationName(QStringLiteral("scada"));

    // qrc 前缀为 "/"，文件放在 resources/style/ 下，资源路径即 :/style/common.qss
    QFile qss(QStringLiteral(":/style/common.qss"));
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(QString::fromUtf8(qss.readAll()));
        qss.close();
    }

    // 登录是进入主界面的唯一入口：取消/关闭窗口直接退出，不创建主窗口
    LoginDialog login;
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }

    MainWindow w;
    w.show();
    return QApplication::exec();
}
