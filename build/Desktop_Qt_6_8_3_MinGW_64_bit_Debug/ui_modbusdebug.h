/********************************************************************************
** Form generated from reading UI file 'modbusdebug.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODBUSDEBUG_H
#define UI_MODBUSDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModbusDebug
{
public:
    QProgressBar *progressBar;

    void setupUi(QWidget *ModbusDebug)
    {
        if (ModbusDebug->objectName().isEmpty())
            ModbusDebug->setObjectName("ModbusDebug");
        ModbusDebug->resize(1042, 695);
        progressBar = new QProgressBar(ModbusDebug);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(320, 270, 411, 121));
        progressBar->setValue(89);

        retranslateUi(ModbusDebug);

        QMetaObject::connectSlotsByName(ModbusDebug);
    } // setupUi

    void retranslateUi(QWidget *ModbusDebug)
    {
        ModbusDebug->setWindowTitle(QCoreApplication::translate("ModbusDebug", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModbusDebug: public Ui_ModbusDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUSDEBUG_H
