#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // qrc 前缀为 "/"，文件放在 resources/style/ 下，资源路径即 :/style/common.qss
    QFile qss(QStringLiteral(":/style/common.qss"));
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(QString::fromUtf8(qss.readAll()));
        qss.close();
    }

    MainWindow w;
    w.show();
    return QApplication::exec();
}
