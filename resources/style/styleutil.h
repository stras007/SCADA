#ifndef STYLEUTIL_H
#define STYLEUTIL_H

/**
 * 页面专属 qss 加载小工具（resources.qrc 中 /qss 前缀）。
 * 各页面构造函数里一行调用，替代重复的 QFile 打开模板代码。
 */

#include <QFile>
#include <QWidget>

inline void applyPageQss(QWidget *w, const QString &resource)
{
    QFile f(resource);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
        w->setStyleSheet(QString::fromUtf8(f.readAll()));
}

#endif // STYLEUTIL_H
