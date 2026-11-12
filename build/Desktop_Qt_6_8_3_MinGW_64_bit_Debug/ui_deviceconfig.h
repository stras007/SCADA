/********************************************************************************
** Form generated from reading UI file 'deviceconfig.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICECONFIG_H
#define UI_DEVICECONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceConfig
{
public:
    QCalendarWidget *calendarWidget;

    void setupUi(QWidget *DeviceConfig)
    {
        if (DeviceConfig->objectName().isEmpty())
            DeviceConfig->setObjectName("DeviceConfig");
        DeviceConfig->resize(1157, 738);
        calendarWidget = new QCalendarWidget(DeviceConfig);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(410, 240, 296, 229));

        retranslateUi(DeviceConfig);

        QMetaObject::connectSlotsByName(DeviceConfig);
    } // setupUi

    void retranslateUi(QWidget *DeviceConfig)
    {
        DeviceConfig->setWindowTitle(QCoreApplication::translate("DeviceConfig", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceConfig: public Ui_DeviceConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICECONFIG_H
