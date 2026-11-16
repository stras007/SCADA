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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModbusDebug
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollAreaPage;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hboxTitle;
    QLabel *lblPageTitle;
    QSpacerItem *spTitle;
    QLabel *lblPageInfo;
    QFrame *panelConn;
    QVBoxLayout *layPanelConn;
    QLabel *lblConnTitle;
    QHBoxLayout *hboxConn;
    QLabel *lblHost;
    QLineEdit *editHost;
    QLabel *lblPort;
    QLineEdit *editPort;
    QPushButton *btnConnect;
    QSpacerItem *spConn;
    QLabel *lblConnState;
    QFrame *panelRealtime;
    QVBoxLayout *layPanelRealtime;
    QLabel *lblRtTitle;
    QTableWidget *realtimeTable;
    QFrame *panelPcs;
    QVBoxLayout *layPanelPcs;
    QLabel *lblPcsTitle;
    QHBoxLayout *hboxPcsRow1;
    QHBoxLayout *hboxPcsG1;
    QLabel *lblCapP;
    QLabel *lblPcsPower;
    QHBoxLayout *hboxPcsG2;
    QLabel *lblCapAcV;
    QLabel *lblPcsAcV;
    QHBoxLayout *hboxPcsG3;
    QLabel *lblCapFreq;
    QLabel *lblPcsFreq;
    QHBoxLayout *hboxPcsG4;
    QLabel *lblCapState;
    QLabel *lblPcsState;
    QSpacerItem *spPcsRow1;
    QHBoxLayout *hboxPcsRow2;
    QHBoxLayout *hboxPcsG5;
    QLabel *lblCapDayChg;
    QLabel *lblPcsDayChg;
    QHBoxLayout *hboxPcsG6;
    QLabel *lblCapDayDis;
    QLabel *lblPcsDayDis;
    QHBoxLayout *hboxPcsG7;
    QLabel *lblCapTotalChg;
    QLabel *lblPcsTotalChg;
    QHBoxLayout *hboxPcsG8;
    QLabel *lblCapTotalDis;
    QLabel *lblPcsTotalDis;
    QSpacerItem *spPcsRow2;
    QHBoxLayout *hboxRegs;
    QFrame *panelReadWrite;
    QVBoxLayout *layPanelReadWrite;
    QLabel *lblRwTitle;
    QHBoxLayout *hboxRw1;
    QLabel *lblSlave;
    QLineEdit *editSlaveId;
    QLabel *lblAddr;
    QLineEdit *editStartAddr;
    QLabel *lblFunc;
    QLineEdit *editFuncCode;
    QLabel *lblCount;
    QLineEdit *editCount;
    QHBoxLayout *hboxRw2;
    QLabel *lblWriteVal;
    QLineEdit *editWriteValue;
    QPushButton *btnRead;
    QPushButton *btnWrite;
    QSpacerItem *spRw2;
    QFrame *panelRegValues;
    QVBoxLayout *layPanelRegValues;
    QLabel *lblRvTitle;
    QTableWidget *regValueTable;
    QFrame *panelLog;
    QVBoxLayout *layPanelLog;
    QLabel *lblLogTitle;
    QPlainTextEdit *logEdit;
    QSpacerItem *spBottom;

    void setupUi(QMainWindow *ModbusDebug)
    {
        if (ModbusDebug->objectName().isEmpty())
            ModbusDebug->setObjectName("ModbusDebug");
        ModbusDebug->resize(1096, 820);
        centralwidget = new QWidget(ModbusDebug);
        centralwidget->setObjectName("centralwidget");
        scrollAreaPage = new QScrollArea(centralwidget);
        scrollAreaPage->setObjectName("scrollAreaPage");
        scrollAreaPage->setGeometry(QRect(0, 0, 1096, 820));
        scrollAreaPage->setFrameShape(QFrame::Shape::NoFrame);
        scrollAreaPage->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollAreaPage->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1096, 820));
        mainLayout = new QVBoxLayout(scrollAreaWidgetContents);
        mainLayout->setSpacing(8);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(12, 10, 12, 12);
        hboxTitle = new QHBoxLayout();
        hboxTitle->setObjectName("hboxTitle");
        lblPageTitle = new QLabel(scrollAreaWidgetContents);
        lblPageTitle->setObjectName("lblPageTitle");

        hboxTitle->addWidget(lblPageTitle);

        spTitle = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxTitle->addItem(spTitle);

        lblPageInfo = new QLabel(scrollAreaWidgetContents);
        lblPageInfo->setObjectName("lblPageInfo");

        hboxTitle->addWidget(lblPageInfo);


        mainLayout->addLayout(hboxTitle);

        panelConn = new QFrame(scrollAreaWidgetContents);
        panelConn->setObjectName("panelConn");
        layPanelConn = new QVBoxLayout(panelConn);
        layPanelConn->setSpacing(8);
        layPanelConn->setObjectName("layPanelConn");
        lblConnTitle = new QLabel(panelConn);
        lblConnTitle->setObjectName("lblConnTitle");

        layPanelConn->addWidget(lblConnTitle);

        hboxConn = new QHBoxLayout();
        hboxConn->setObjectName("hboxConn");
        lblHost = new QLabel(panelConn);
        lblHost->setObjectName("lblHost");

        hboxConn->addWidget(lblHost);

        editHost = new QLineEdit(panelConn);
        editHost->setObjectName("editHost");
        editHost->setMinimumSize(QSize(140, 0));

        hboxConn->addWidget(editHost);

        lblPort = new QLabel(panelConn);
        lblPort->setObjectName("lblPort");

        hboxConn->addWidget(lblPort);

        editPort = new QLineEdit(panelConn);
        editPort->setObjectName("editPort");
        editPort->setMaximumSize(QSize(70, 16777215));

        hboxConn->addWidget(editPort);

        btnConnect = new QPushButton(panelConn);
        btnConnect->setObjectName("btnConnect");
        btnConnect->setProperty("primary", QVariant(true));

        hboxConn->addWidget(btnConnect);

        spConn = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxConn->addItem(spConn);

        lblConnState = new QLabel(panelConn);
        lblConnState->setObjectName("lblConnState");
        lblConnState->setProperty("online", QVariant(false));

        hboxConn->addWidget(lblConnState);


        layPanelConn->addLayout(hboxConn);


        mainLayout->addWidget(panelConn);

        panelRealtime = new QFrame(scrollAreaWidgetContents);
        panelRealtime->setObjectName("panelRealtime");
        layPanelRealtime = new QVBoxLayout(panelRealtime);
        layPanelRealtime->setObjectName("layPanelRealtime");
        lblRtTitle = new QLabel(panelRealtime);
        lblRtTitle->setObjectName("lblRtTitle");

        layPanelRealtime->addWidget(lblRtTitle);

        realtimeTable = new QTableWidget(panelRealtime);
        if (realtimeTable->columnCount() < 6)
            realtimeTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        realtimeTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        realtimeTable->setObjectName("realtimeTable");
        realtimeTable->setMinimumSize(QSize(0, 170));
        realtimeTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        realtimeTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        realtimeTable->horizontalHeader()->setStretchLastSection(true);
        realtimeTable->verticalHeader()->setVisible(false);

        layPanelRealtime->addWidget(realtimeTable);


        mainLayout->addWidget(panelRealtime);

        panelPcs = new QFrame(scrollAreaWidgetContents);
        panelPcs->setObjectName("panelPcs");
        layPanelPcs = new QVBoxLayout(panelPcs);
        layPanelPcs->setObjectName("layPanelPcs");
        lblPcsTitle = new QLabel(panelPcs);
        lblPcsTitle->setObjectName("lblPcsTitle");

        layPanelPcs->addWidget(lblPcsTitle);

        hboxPcsRow1 = new QHBoxLayout();
        hboxPcsRow1->setObjectName("hboxPcsRow1");
        hboxPcsG1 = new QHBoxLayout();
        hboxPcsG1->setObjectName("hboxPcsG1");
        lblCapP = new QLabel(panelPcs);
        lblCapP->setObjectName("lblCapP");

        hboxPcsG1->addWidget(lblCapP);

        lblPcsPower = new QLabel(panelPcs);
        lblPcsPower->setObjectName("lblPcsPower");

        hboxPcsG1->addWidget(lblPcsPower);


        hboxPcsRow1->addLayout(hboxPcsG1);

        hboxPcsG2 = new QHBoxLayout();
        hboxPcsG2->setObjectName("hboxPcsG2");
        lblCapAcV = new QLabel(panelPcs);
        lblCapAcV->setObjectName("lblCapAcV");

        hboxPcsG2->addWidget(lblCapAcV);

        lblPcsAcV = new QLabel(panelPcs);
        lblPcsAcV->setObjectName("lblPcsAcV");

        hboxPcsG2->addWidget(lblPcsAcV);


        hboxPcsRow1->addLayout(hboxPcsG2);

        hboxPcsG3 = new QHBoxLayout();
        hboxPcsG3->setObjectName("hboxPcsG3");
        lblCapFreq = new QLabel(panelPcs);
        lblCapFreq->setObjectName("lblCapFreq");

        hboxPcsG3->addWidget(lblCapFreq);

        lblPcsFreq = new QLabel(panelPcs);
        lblPcsFreq->setObjectName("lblPcsFreq");

        hboxPcsG3->addWidget(lblPcsFreq);


        hboxPcsRow1->addLayout(hboxPcsG3);

        hboxPcsG4 = new QHBoxLayout();
        hboxPcsG4->setObjectName("hboxPcsG4");
        lblCapState = new QLabel(panelPcs);
        lblCapState->setObjectName("lblCapState");

        hboxPcsG4->addWidget(lblCapState);

        lblPcsState = new QLabel(panelPcs);
        lblPcsState->setObjectName("lblPcsState");

        hboxPcsG4->addWidget(lblPcsState);


        hboxPcsRow1->addLayout(hboxPcsG4);

        spPcsRow1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxPcsRow1->addItem(spPcsRow1);


        layPanelPcs->addLayout(hboxPcsRow1);

        hboxPcsRow2 = new QHBoxLayout();
        hboxPcsRow2->setObjectName("hboxPcsRow2");
        hboxPcsG5 = new QHBoxLayout();
        hboxPcsG5->setObjectName("hboxPcsG5");
        lblCapDayChg = new QLabel(panelPcs);
        lblCapDayChg->setObjectName("lblCapDayChg");

        hboxPcsG5->addWidget(lblCapDayChg);

        lblPcsDayChg = new QLabel(panelPcs);
        lblPcsDayChg->setObjectName("lblPcsDayChg");

        hboxPcsG5->addWidget(lblPcsDayChg);


        hboxPcsRow2->addLayout(hboxPcsG5);

        hboxPcsG6 = new QHBoxLayout();
        hboxPcsG6->setObjectName("hboxPcsG6");
        lblCapDayDis = new QLabel(panelPcs);
        lblCapDayDis->setObjectName("lblCapDayDis");

        hboxPcsG6->addWidget(lblCapDayDis);

        lblPcsDayDis = new QLabel(panelPcs);
        lblPcsDayDis->setObjectName("lblPcsDayDis");

        hboxPcsG6->addWidget(lblPcsDayDis);


        hboxPcsRow2->addLayout(hboxPcsG6);

        hboxPcsG7 = new QHBoxLayout();
        hboxPcsG7->setObjectName("hboxPcsG7");
        lblCapTotalChg = new QLabel(panelPcs);
        lblCapTotalChg->setObjectName("lblCapTotalChg");

        hboxPcsG7->addWidget(lblCapTotalChg);

        lblPcsTotalChg = new QLabel(panelPcs);
        lblPcsTotalChg->setObjectName("lblPcsTotalChg");

        hboxPcsG7->addWidget(lblPcsTotalChg);


        hboxPcsRow2->addLayout(hboxPcsG7);

        hboxPcsG8 = new QHBoxLayout();
        hboxPcsG8->setObjectName("hboxPcsG8");
        lblCapTotalDis = new QLabel(panelPcs);
        lblCapTotalDis->setObjectName("lblCapTotalDis");

        hboxPcsG8->addWidget(lblCapTotalDis);

        lblPcsTotalDis = new QLabel(panelPcs);
        lblPcsTotalDis->setObjectName("lblPcsTotalDis");

        hboxPcsG8->addWidget(lblPcsTotalDis);


        hboxPcsRow2->addLayout(hboxPcsG8);

        spPcsRow2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxPcsRow2->addItem(spPcsRow2);


        layPanelPcs->addLayout(hboxPcsRow2);


        mainLayout->addWidget(panelPcs);

        hboxRegs = new QHBoxLayout();
        hboxRegs->setObjectName("hboxRegs");
        panelReadWrite = new QFrame(scrollAreaWidgetContents);
        panelReadWrite->setObjectName("panelReadWrite");
        layPanelReadWrite = new QVBoxLayout(panelReadWrite);
        layPanelReadWrite->setSpacing(8);
        layPanelReadWrite->setObjectName("layPanelReadWrite");
        lblRwTitle = new QLabel(panelReadWrite);
        lblRwTitle->setObjectName("lblRwTitle");

        layPanelReadWrite->addWidget(lblRwTitle);

        hboxRw1 = new QHBoxLayout();
        hboxRw1->setObjectName("hboxRw1");
        lblSlave = new QLabel(panelReadWrite);
        lblSlave->setObjectName("lblSlave");

        hboxRw1->addWidget(lblSlave);

        editSlaveId = new QLineEdit(panelReadWrite);
        editSlaveId->setObjectName("editSlaveId");
        editSlaveId->setMaximumSize(QSize(60, 16777215));

        hboxRw1->addWidget(editSlaveId);

        lblAddr = new QLabel(panelReadWrite);
        lblAddr->setObjectName("lblAddr");

        hboxRw1->addWidget(lblAddr);

        editStartAddr = new QLineEdit(panelReadWrite);
        editStartAddr->setObjectName("editStartAddr");
        editStartAddr->setMaximumSize(QSize(90, 16777215));

        hboxRw1->addWidget(editStartAddr);

        lblFunc = new QLabel(panelReadWrite);
        lblFunc->setObjectName("lblFunc");

        hboxRw1->addWidget(lblFunc);

        editFuncCode = new QLineEdit(panelReadWrite);
        editFuncCode->setObjectName("editFuncCode");
        editFuncCode->setMaximumSize(QSize(60, 16777215));

        hboxRw1->addWidget(editFuncCode);

        lblCount = new QLabel(panelReadWrite);
        lblCount->setObjectName("lblCount");

        hboxRw1->addWidget(lblCount);

        editCount = new QLineEdit(panelReadWrite);
        editCount->setObjectName("editCount");
        editCount->setMaximumSize(QSize(60, 16777215));

        hboxRw1->addWidget(editCount);


        layPanelReadWrite->addLayout(hboxRw1);

        hboxRw2 = new QHBoxLayout();
        hboxRw2->setObjectName("hboxRw2");
        lblWriteVal = new QLabel(panelReadWrite);
        lblWriteVal->setObjectName("lblWriteVal");

        hboxRw2->addWidget(lblWriteVal);

        editWriteValue = new QLineEdit(panelReadWrite);
        editWriteValue->setObjectName("editWriteValue");
        editWriteValue->setMaximumSize(QSize(80, 16777215));

        hboxRw2->addWidget(editWriteValue);

        btnRead = new QPushButton(panelReadWrite);
        btnRead->setObjectName("btnRead");
        btnRead->setProperty("primary", QVariant(true));

        hboxRw2->addWidget(btnRead);

        btnWrite = new QPushButton(panelReadWrite);
        btnWrite->setObjectName("btnWrite");

        hboxRw2->addWidget(btnWrite);

        spRw2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxRw2->addItem(spRw2);


        layPanelReadWrite->addLayout(hboxRw2);


        hboxRegs->addWidget(panelReadWrite);

        panelRegValues = new QFrame(scrollAreaWidgetContents);
        panelRegValues->setObjectName("panelRegValues");
        layPanelRegValues = new QVBoxLayout(panelRegValues);
        layPanelRegValues->setObjectName("layPanelRegValues");
        lblRvTitle = new QLabel(panelRegValues);
        lblRvTitle->setObjectName("lblRvTitle");

        layPanelRegValues->addWidget(lblRvTitle);

        regValueTable = new QTableWidget(panelRegValues);
        if (regValueTable->columnCount() < 3)
            regValueTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        regValueTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        regValueTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        regValueTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        regValueTable->setObjectName("regValueTable");
        regValueTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        regValueTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        regValueTable->horizontalHeader()->setStretchLastSection(true);
        regValueTable->verticalHeader()->setVisible(false);

        layPanelRegValues->addWidget(regValueTable);


        hboxRegs->addWidget(panelRegValues);

        hboxRegs->setStretch(0, 1);
        hboxRegs->setStretch(1, 1);

        mainLayout->addLayout(hboxRegs);

        panelLog = new QFrame(scrollAreaWidgetContents);
        panelLog->setObjectName("panelLog");
        layPanelLog = new QVBoxLayout(panelLog);
        layPanelLog->setObjectName("layPanelLog");
        lblLogTitle = new QLabel(panelLog);
        lblLogTitle->setObjectName("lblLogTitle");

        layPanelLog->addWidget(lblLogTitle);

        logEdit = new QPlainTextEdit(panelLog);
        logEdit->setObjectName("logEdit");
        logEdit->setMinimumSize(QSize(0, 110));
        logEdit->setReadOnly(true);

        layPanelLog->addWidget(logEdit);


        mainLayout->addWidget(panelLog);

        spBottom = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(spBottom);

        scrollAreaPage->setWidget(scrollAreaWidgetContents);
        ModbusDebug->setCentralWidget(centralwidget);

        retranslateUi(ModbusDebug);

        QMetaObject::connectSlotsByName(ModbusDebug);
    } // setupUi

    void retranslateUi(QMainWindow *ModbusDebug)
    {
        ModbusDebug->setWindowTitle(QCoreApplication::translate("ModbusDebug", "MainWindow", nullptr));
        lblPageTitle->setText(QCoreApplication::translate("ModbusDebug", "Modbus \351\200\232\350\256\257\350\260\203\350\257\225", nullptr));
        lblPageTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "pageTitle", nullptr)));
        lblPageInfo->setText(QCoreApplication::translate("ModbusDebug", "\345\212\250\346\200\201\347\260\207\347\273\204\351\205\215\347\275\256 \302\267 \345\256\236\346\227\266\346\225\260\346\215\256\350\275\256\350\257\242", nullptr));
        lblPageInfo->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "pageInfo", nullptr)));
        panelConn->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblConnTitle->setText(QCoreApplication::translate("ModbusDebug", "\351\200\232\350\256\257\350\277\236\346\216\245", nullptr));
        lblConnTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
        lblHost->setText(QCoreApplication::translate("ModbusDebug", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        lblHost->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editHost->setText(QCoreApplication::translate("ModbusDebug", "127.0.0.1", nullptr));
        lblPort->setText(QCoreApplication::translate("ModbusDebug", "\347\253\257\345\217\243", nullptr));
        lblPort->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editPort->setText(QCoreApplication::translate("ModbusDebug", "1502", nullptr));
        editPort->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        btnConnect->setText(QCoreApplication::translate("ModbusDebug", "\350\277\236\346\216\245", nullptr));
        lblConnState->setText(QCoreApplication::translate("ModbusDebug", "\346\234\252\350\277\236\346\216\245", nullptr));
        lblConnState->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "stateText", nullptr)));
        panelRealtime->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblRtTitle->setText(QCoreApplication::translate("ModbusDebug", "\345\256\236\346\227\266\346\225\260\346\215\256\357\274\210\350\275\256\350\257\242\350\207\252\345\212\250\345\210\267\346\226\260 \302\267 \346\216\247\345\210\266\345\217\260\345\220\214\346\255\245\350\276\223\345\207\272\357\274\211", nullptr));
        lblRtTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
        QTableWidgetItem *___qtablewidgetitem = realtimeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ModbusDebug", "\347\260\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = realtimeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ModbusDebug", "\347\224\265\345\216\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = realtimeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ModbusDebug", "\347\224\265\346\265\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = realtimeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ModbusDebug", "SOC", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = realtimeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ModbusDebug", "\346\234\200\351\253\230\346\270\251\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = realtimeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ModbusDebug", "\347\212\266\346\200\201", nullptr));
        panelPcs->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblPcsTitle->setText(QCoreApplication::translate("ModbusDebug", "PCS \351\200\206\345\217\230\345\231\250 \302\267 \345\205\205\346\224\276\347\224\265\347\273\237\350\256\241\357\274\210\350\207\252\345\212\250\350\275\256\350\257\242\357\274\211", nullptr));
        lblPcsTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
        lblCapP->setText(QCoreApplication::translate("ModbusDebug", "\346\234\211\345\212\237\345\212\237\347\216\207", nullptr));
        lblCapP->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsPower->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsPower->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapAcV->setText(QCoreApplication::translate("ModbusDebug", "\344\272\244\346\265\201\347\224\265\345\216\213", nullptr));
        lblCapAcV->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsAcV->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsAcV->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapFreq->setText(QCoreApplication::translate("ModbusDebug", "\351\242\221\347\216\207", nullptr));
        lblCapFreq->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsFreq->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsFreq->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapState->setText(QCoreApplication::translate("ModbusDebug", "\347\212\266\346\200\201", nullptr));
        lblCapState->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsState->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsState->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapDayChg->setText(QCoreApplication::translate("ModbusDebug", "\346\227\245\345\205\205\347\224\265\351\207\217", nullptr));
        lblCapDayChg->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsDayChg->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsDayChg->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapDayDis->setText(QCoreApplication::translate("ModbusDebug", "\346\227\245\346\224\276\347\224\265\351\207\217", nullptr));
        lblCapDayDis->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsDayDis->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsDayDis->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapTotalChg->setText(QCoreApplication::translate("ModbusDebug", "\347\264\257\350\256\241\345\205\205\347\224\265\351\207\217", nullptr));
        lblCapTotalChg->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsTotalChg->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsTotalChg->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        lblCapTotalDis->setText(QCoreApplication::translate("ModbusDebug", "\347\264\257\350\256\241\346\224\276\347\224\265\351\207\217", nullptr));
        lblCapTotalDis->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        lblPcsTotalDis->setText(QCoreApplication::translate("ModbusDebug", "-", nullptr));
        lblPcsTotalDis->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "valueText", nullptr)));
        panelReadWrite->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblRwTitle->setText(QCoreApplication::translate("ModbusDebug", "\345\257\204\345\255\230\345\231\250\346\211\213\345\212\250\350\257\273\345\206\231", nullptr));
        lblRwTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
        lblSlave->setText(QCoreApplication::translate("ModbusDebug", "\344\273\216\347\253\231\345\234\260\345\235\200", nullptr));
        lblSlave->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editSlaveId->setText(QCoreApplication::translate("ModbusDebug", "1", nullptr));
        editSlaveId->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        lblAddr->setText(QCoreApplication::translate("ModbusDebug", "\350\265\267\345\247\213\345\234\260\345\235\200", nullptr));
        lblAddr->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editStartAddr->setText(QCoreApplication::translate("ModbusDebug", "0x0100", nullptr));
        editStartAddr->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        lblFunc->setText(QCoreApplication::translate("ModbusDebug", "\345\212\237\350\203\275\347\240\201", nullptr));
        lblFunc->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editFuncCode->setText(QCoreApplication::translate("ModbusDebug", "03", nullptr));
        editFuncCode->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        lblCount->setText(QCoreApplication::translate("ModbusDebug", "\346\225\260\351\207\217", nullptr));
        lblCount->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editCount->setText(QCoreApplication::translate("ModbusDebug", "10", nullptr));
        editCount->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        lblWriteVal->setText(QCoreApplication::translate("ModbusDebug", "\345\206\231\345\205\245\345\200\274", nullptr));
        lblWriteVal->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "descText", nullptr)));
        editWriteValue->setText(QCoreApplication::translate("ModbusDebug", "0", nullptr));
        editWriteValue->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "addrEdit", nullptr)));
        btnRead->setText(QCoreApplication::translate("ModbusDebug", "\350\257\273\345\217\226", nullptr));
        btnWrite->setText(QCoreApplication::translate("ModbusDebug", "\345\206\231\345\205\245", nullptr));
        panelRegValues->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblRvTitle->setText(QCoreApplication::translate("ModbusDebug", "\345\257\204\345\255\230\345\231\250\345\200\274\345\210\227\350\241\250", nullptr));
        lblRvTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
        QTableWidgetItem *___qtablewidgetitem6 = regValueTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ModbusDebug", "\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = regValueTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ModbusDebug", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = regValueTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ModbusDebug", "\346\230\240\345\260\204", nullptr));
        panelLog->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panel", nullptr)));
        lblLogTitle->setText(QCoreApplication::translate("ModbusDebug", "\351\200\232\350\256\257\350\257\212\346\226\255 / \346\227\245\345\277\227", nullptr));
        lblLogTitle->setProperty("class", QVariant(QCoreApplication::translate("ModbusDebug", "panelTitle", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class ModbusDebug: public Ui_ModbusDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUSDEBUG_H
