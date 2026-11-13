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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceConfig
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *panelPcs;
    QLabel *lblPcsTitle;
    QSpacerItem *spPcs1;
    QLabel *lblPcsSlave;
    QSpinBox *spinPcsSlave;
    QSpacerItem *spPcs2;
    QLabel *lblDevTitle;
    QWidget *layoutWidget_2;
    QHBoxLayout *hboxState;
    QLabel *lblState;
    QSpacerItem *spState_2;
    QLabel *lblStatePath;
    QTableWidget *deviceTable;
    QWidget *widget;
    QHBoxLayout *hboxDevBtns;
    QPushButton *btnAddDevice;
    QPushButton *btnEditDevice;
    QPushButton *btnRemoveDevice;
    QSpacerItem *spDevBtns;
    QPushButton *btnRevert;
    QPushButton *btnApply;
    QWidget *widget1;
    QHBoxLayout *hboxTitle;
    QLabel *lblPageInfo;
    QSpacerItem *spState;
    QLabel *lblPageTitle;

    void setupUi(QWidget *DeviceConfig)
    {
        if (DeviceConfig->objectName().isEmpty())
            DeviceConfig->setObjectName("DeviceConfig");
        DeviceConfig->resize(1145, 780);
        layoutWidget = new QWidget(DeviceConfig);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(80, 160, 981, 41));
        panelPcs = new QHBoxLayout(layoutWidget);
        panelPcs->setObjectName("panelPcs");
        panelPcs->setContentsMargins(0, 0, 0, 0);
        lblPcsTitle = new QLabel(layoutWidget);
        lblPcsTitle->setObjectName("lblPcsTitle");

        panelPcs->addWidget(lblPcsTitle);

        spPcs1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        panelPcs->addItem(spPcs1);

        lblPcsSlave = new QLabel(layoutWidget);
        lblPcsSlave->setObjectName("lblPcsSlave");

        panelPcs->addWidget(lblPcsSlave);

        spinPcsSlave = new QSpinBox(layoutWidget);
        spinPcsSlave->setObjectName("spinPcsSlave");
        spinPcsSlave->setEnabled(true);

        panelPcs->addWidget(spinPcsSlave);

        spPcs2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        panelPcs->addItem(spPcs2);

        lblDevTitle = new QLabel(DeviceConfig);
        lblDevTitle->setObjectName("lblDevTitle");
        lblDevTitle->setGeometry(QRect(80, 240, 391, 31));
        layoutWidget_2 = new QWidget(DeviceConfig);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(80, 640, 981, 41));
        hboxState = new QHBoxLayout(layoutWidget_2);
        hboxState->setObjectName("hboxState");
        hboxState->setContentsMargins(0, 0, 0, 0);
        lblState = new QLabel(layoutWidget_2);
        lblState->setObjectName("lblState");

        hboxState->addWidget(lblState);

        spState_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxState->addItem(spState_2);

        lblStatePath = new QLabel(layoutWidget_2);
        lblStatePath->setObjectName("lblStatePath");

        hboxState->addWidget(lblStatePath);

        deviceTable = new QTableWidget(DeviceConfig);
        if (deviceTable->columnCount() < 8)
            deviceTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        deviceTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        deviceTable->setObjectName("deviceTable");
        deviceTable->setGeometry(QRect(80, 320, 981, 321));
        widget = new QWidget(DeviceConfig);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(80, 280, 981, 41));
        hboxDevBtns = new QHBoxLayout(widget);
        hboxDevBtns->setObjectName("hboxDevBtns");
        hboxDevBtns->setContentsMargins(0, 0, 0, 0);
        btnAddDevice = new QPushButton(widget);
        btnAddDevice->setObjectName("btnAddDevice");

        hboxDevBtns->addWidget(btnAddDevice);

        btnEditDevice = new QPushButton(widget);
        btnEditDevice->setObjectName("btnEditDevice");

        hboxDevBtns->addWidget(btnEditDevice);

        btnRemoveDevice = new QPushButton(widget);
        btnRemoveDevice->setObjectName("btnRemoveDevice");

        hboxDevBtns->addWidget(btnRemoveDevice);

        spDevBtns = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxDevBtns->addItem(spDevBtns);

        btnRevert = new QPushButton(widget);
        btnRevert->setObjectName("btnRevert");

        hboxDevBtns->addWidget(btnRevert);

        btnApply = new QPushButton(widget);
        btnApply->setObjectName("btnApply");

        hboxDevBtns->addWidget(btnApply);

        widget1 = new QWidget(DeviceConfig);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(80, 80, 981, 41));
        hboxTitle = new QHBoxLayout(widget1);
        hboxTitle->setObjectName("hboxTitle");
        hboxTitle->setContentsMargins(0, 0, 0, 0);
        lblPageInfo = new QLabel(widget1);
        lblPageInfo->setObjectName("lblPageInfo");

        hboxTitle->addWidget(lblPageInfo);

        spState = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxTitle->addItem(spState);

        lblPageTitle = new QLabel(widget1);
        lblPageTitle->setObjectName("lblPageTitle");

        hboxTitle->addWidget(lblPageTitle);


        retranslateUi(DeviceConfig);

        QMetaObject::connectSlotsByName(DeviceConfig);
    } // setupUi

    void retranslateUi(QWidget *DeviceConfig)
    {
        DeviceConfig->setWindowTitle(QCoreApplication::translate("DeviceConfig", "Form", nullptr));
        lblPcsTitle->setText(QCoreApplication::translate("DeviceConfig", "PCS \351\200\206\345\217\230\345\231\250 \357\274\210\345\220\214\351\223\276\350\267\257\347\213\254\347\253\213\344\273\216\347\253\231\357\274\211", nullptr));
        lblPcsSlave->setText(QCoreApplication::translate("DeviceConfig", "\344\273\216\347\253\231\345\234\260\345\235\200 0\344\270\215\345\220\257\347\224\250", nullptr));
        lblDevTitle->setText(QCoreApplication::translate("DeviceConfig", "\347\224\265\346\261\240\347\260\207\350\256\276\345\244\207\345\217\260\350\264\246\357\274\210\345\217\214\345\207\273\350\241\214\347\274\226\350\276\221\345\217\202\346\225\260\357\274\214\350\256\276\345\244\207ID\344\270\272\344\270\273\351\224\256\357\274\211", nullptr));
        lblState->setText(QCoreApplication::translate("DeviceConfig", "\351\205\215\347\275\256\347\212\266\346\200\201: \345\267\262\344\270\216\345\267\245\347\250\213\346\226\207\344\273\266\345\220\214\346\255\245", nullptr));
        lblStatePath->setText(QCoreApplication::translate("DeviceConfig", "project_config.json", nullptr));
        QTableWidgetItem *___qtablewidgetitem = deviceTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DeviceConfig", "\350\256\276\345\244\207ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = deviceTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DeviceConfig", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = deviceTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DeviceConfig", "\347\202\271\350\241\250\346\250\241\346\235\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = deviceTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DeviceConfig", "\345\202\250\350\203\275\345\215\225\345\205\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = deviceTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DeviceConfig", "\344\273\216\347\253\231\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = deviceTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DeviceConfig", "\351\242\235\345\256\232\347\224\265\345\216\213(V)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = deviceTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DeviceConfig", "\351\242\235\345\256\232\345\256\271\351\207\217(kWh)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = deviceTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("DeviceConfig", "\351\207\207\351\233\206\347\212\266\346\200\201", nullptr));
        btnAddDevice->setText(QCoreApplication::translate("DeviceConfig", "\346\226\260\345\242\236", nullptr));
        btnEditDevice->setText(QCoreApplication::translate("DeviceConfig", "\347\274\226\350\276\221", nullptr));
        btnRemoveDevice->setText(QCoreApplication::translate("DeviceConfig", "\345\210\240\351\231\244", nullptr));
        btnRevert->setText(QCoreApplication::translate("DeviceConfig", "\350\277\230\345\216\237", nullptr));
        btnApply->setText(QCoreApplication::translate("DeviceConfig", "\344\270\213\345\217\221\351\205\215\347\275\256", nullptr));
        lblPageInfo->setText(QCoreApplication::translate("DeviceConfig", "\350\256\276\345\244\207\347\273\204\346\200\201", nullptr));
        lblPageTitle->setText(QCoreApplication::translate("DeviceConfig", "\345\217\260\350\264\246\347\274\226\350\276\221\344\270\272\350\215\211\347\250\277\357\274\214\347\202\271\345\207\273\"\344\270\213\345\217\221\351\205\215\347\275\256\"\346\240\241\351\252\214\357\274\214\345\206\231\345\205\245\345\267\245\347\250\213\346\226\207\344\273\266\345\271\266\347\253\213\345\215\263\347\224\237\346\225\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceConfig: public Ui_DeviceConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICECONFIG_H
