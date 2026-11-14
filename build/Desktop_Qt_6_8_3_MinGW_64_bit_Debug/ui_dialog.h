/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tabBasic;
    QFormLayout *formBasic;
    QLabel *lblDevId;
    QLabel *lblDevIdValue;
    QLabel *lblName;
    QLineEdit *editName;
    QLabel *lblModel;
    QComboBox *cmbModel;
    QLabel *lblUnit;
    QComboBox *cmbUnit;
    QLabel *lblSlave;
    QSpinBox *spinSlave;
    QLabel *lblEnabled;
    QCheckBox *chkEnabled;
    QWidget *tabRated;
    QFormLayout *formRated;
    QLabel *lblRatedV;
    QDoubleSpinBox *spinRatedV;
    QLabel *lblCapacity;
    QDoubleSpinBox *spinCapacity;
    QLabel *lblChgI;
    QDoubleSpinBox *spinChgI;
    QLabel *lblDisI;
    QDoubleSpinBox *spinDisI;
    QLabel *lblSerial;
    QSpinBox *spinSerial;
    QWidget *tabAlarm;
    QFormLayout *formAlarm;
    QLabel *lblOv;
    QDoubleSpinBox *spinOvWarn;
    QLabel *lblOvF;
    QDoubleSpinBox *spinOvFault;
    QLabel *lblUv;
    QDoubleSpinBox *spinUvWarn;
    QLabel *lblUvF;
    QDoubleSpinBox *spinUvFault;
    QLabel *lblOt;
    QDoubleSpinBox *spinOtWarn;
    QLabel *lblOtF;
    QDoubleSpinBox *spinOtFault;
    QLabel *lblLt;
    QDoubleSpinBox *spinLtWarn;
    QLabel *lblLtF;
    QDoubleSpinBox *spinLtFault;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(459, 517);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(21, 41, 418, 408));
        tabBasic = new QWidget();
        tabBasic->setObjectName("tabBasic");
        formBasic = new QFormLayout(tabBasic);
        formBasic->setObjectName("formBasic");
        lblDevId = new QLabel(tabBasic);
        lblDevId->setObjectName("lblDevId");

        formBasic->setWidget(0, QFormLayout::LabelRole, lblDevId);

        lblDevIdValue = new QLabel(tabBasic);
        lblDevIdValue->setObjectName("lblDevIdValue");

        formBasic->setWidget(0, QFormLayout::FieldRole, lblDevIdValue);

        lblName = new QLabel(tabBasic);
        lblName->setObjectName("lblName");

        formBasic->setWidget(1, QFormLayout::LabelRole, lblName);

        editName = new QLineEdit(tabBasic);
        editName->setObjectName("editName");

        formBasic->setWidget(1, QFormLayout::FieldRole, editName);

        lblModel = new QLabel(tabBasic);
        lblModel->setObjectName("lblModel");

        formBasic->setWidget(2, QFormLayout::LabelRole, lblModel);

        cmbModel = new QComboBox(tabBasic);
        cmbModel->addItem(QString());
        cmbModel->addItem(QString());
        cmbModel->addItem(QString());
        cmbModel->setObjectName("cmbModel");

        formBasic->setWidget(2, QFormLayout::FieldRole, cmbModel);

        lblUnit = new QLabel(tabBasic);
        lblUnit->setObjectName("lblUnit");

        formBasic->setWidget(3, QFormLayout::LabelRole, lblUnit);

        cmbUnit = new QComboBox(tabBasic);
        cmbUnit->addItem(QString());
        cmbUnit->addItem(QString());
        cmbUnit->addItem(QString());
        cmbUnit->addItem(QString());
        cmbUnit->setObjectName("cmbUnit");

        formBasic->setWidget(3, QFormLayout::FieldRole, cmbUnit);

        lblSlave = new QLabel(tabBasic);
        lblSlave->setObjectName("lblSlave");

        formBasic->setWidget(4, QFormLayout::LabelRole, lblSlave);

        spinSlave = new QSpinBox(tabBasic);
        spinSlave->setObjectName("spinSlave");
        spinSlave->setMinimum(1);
        spinSlave->setMaximum(247);

        formBasic->setWidget(4, QFormLayout::FieldRole, spinSlave);

        lblEnabled = new QLabel(tabBasic);
        lblEnabled->setObjectName("lblEnabled");

        formBasic->setWidget(5, QFormLayout::LabelRole, lblEnabled);

        chkEnabled = new QCheckBox(tabBasic);
        chkEnabled->setObjectName("chkEnabled");
        chkEnabled->setChecked(true);

        formBasic->setWidget(5, QFormLayout::FieldRole, chkEnabled);

        tabWidget->addTab(tabBasic, QString());
        tabRated = new QWidget();
        tabRated->setObjectName("tabRated");
        formRated = new QFormLayout(tabRated);
        formRated->setObjectName("formRated");
        lblRatedV = new QLabel(tabRated);
        lblRatedV->setObjectName("lblRatedV");

        formRated->setWidget(0, QFormLayout::LabelRole, lblRatedV);

        spinRatedV = new QDoubleSpinBox(tabRated);
        spinRatedV->setObjectName("spinRatedV");
        spinRatedV->setDecimals(1);
        spinRatedV->setMaximum(10000.000000000000000);

        formRated->setWidget(0, QFormLayout::FieldRole, spinRatedV);

        lblCapacity = new QLabel(tabRated);
        lblCapacity->setObjectName("lblCapacity");

        formRated->setWidget(1, QFormLayout::LabelRole, lblCapacity);

        spinCapacity = new QDoubleSpinBox(tabRated);
        spinCapacity->setObjectName("spinCapacity");
        spinCapacity->setDecimals(1);
        spinCapacity->setMaximum(100000.000000000000000);

        formRated->setWidget(1, QFormLayout::FieldRole, spinCapacity);

        lblChgI = new QLabel(tabRated);
        lblChgI->setObjectName("lblChgI");

        formRated->setWidget(2, QFormLayout::LabelRole, lblChgI);

        spinChgI = new QDoubleSpinBox(tabRated);
        spinChgI->setObjectName("spinChgI");
        spinChgI->setDecimals(1);
        spinChgI->setMaximum(10000.000000000000000);

        formRated->setWidget(2, QFormLayout::FieldRole, spinChgI);

        lblDisI = new QLabel(tabRated);
        lblDisI->setObjectName("lblDisI");

        formRated->setWidget(3, QFormLayout::LabelRole, lblDisI);

        spinDisI = new QDoubleSpinBox(tabRated);
        spinDisI->setObjectName("spinDisI");
        spinDisI->setDecimals(1);
        spinDisI->setMaximum(10000.000000000000000);

        formRated->setWidget(3, QFormLayout::FieldRole, spinDisI);

        lblSerial = new QLabel(tabRated);
        lblSerial->setObjectName("lblSerial");

        formRated->setWidget(4, QFormLayout::LabelRole, lblSerial);

        spinSerial = new QSpinBox(tabRated);
        spinSerial->setObjectName("spinSerial");
        spinSerial->setMinimum(1);
        spinSerial->setMaximum(2000);

        formRated->setWidget(4, QFormLayout::FieldRole, spinSerial);

        tabWidget->addTab(tabRated, QString());
        tabAlarm = new QWidget();
        tabAlarm->setObjectName("tabAlarm");
        formAlarm = new QFormLayout(tabAlarm);
        formAlarm->setObjectName("formAlarm");
        lblOv = new QLabel(tabAlarm);
        lblOv->setObjectName("lblOv");

        formAlarm->setWidget(0, QFormLayout::LabelRole, lblOv);

        spinOvWarn = new QDoubleSpinBox(tabAlarm);
        spinOvWarn->setObjectName("spinOvWarn");
        spinOvWarn->setDecimals(1);
        spinOvWarn->setMaximum(10000.000000000000000);

        formAlarm->setWidget(0, QFormLayout::FieldRole, spinOvWarn);

        lblOvF = new QLabel(tabAlarm);
        lblOvF->setObjectName("lblOvF");

        formAlarm->setWidget(1, QFormLayout::LabelRole, lblOvF);

        spinOvFault = new QDoubleSpinBox(tabAlarm);
        spinOvFault->setObjectName("spinOvFault");
        spinOvFault->setDecimals(1);
        spinOvFault->setMaximum(10000.000000000000000);

        formAlarm->setWidget(1, QFormLayout::FieldRole, spinOvFault);

        lblUv = new QLabel(tabAlarm);
        lblUv->setObjectName("lblUv");

        formAlarm->setWidget(2, QFormLayout::LabelRole, lblUv);

        spinUvWarn = new QDoubleSpinBox(tabAlarm);
        spinUvWarn->setObjectName("spinUvWarn");
        spinUvWarn->setDecimals(1);
        spinUvWarn->setMaximum(10000.000000000000000);

        formAlarm->setWidget(2, QFormLayout::FieldRole, spinUvWarn);

        lblUvF = new QLabel(tabAlarm);
        lblUvF->setObjectName("lblUvF");

        formAlarm->setWidget(3, QFormLayout::LabelRole, lblUvF);

        spinUvFault = new QDoubleSpinBox(tabAlarm);
        spinUvFault->setObjectName("spinUvFault");
        spinUvFault->setDecimals(1);
        spinUvFault->setMaximum(10000.000000000000000);

        formAlarm->setWidget(3, QFormLayout::FieldRole, spinUvFault);

        lblOt = new QLabel(tabAlarm);
        lblOt->setObjectName("lblOt");

        formAlarm->setWidget(4, QFormLayout::LabelRole, lblOt);

        spinOtWarn = new QDoubleSpinBox(tabAlarm);
        spinOtWarn->setObjectName("spinOtWarn");
        spinOtWarn->setDecimals(1);
        spinOtWarn->setMinimum(-100.000000000000000);
        spinOtWarn->setMaximum(500.000000000000000);

        formAlarm->setWidget(4, QFormLayout::FieldRole, spinOtWarn);

        lblOtF = new QLabel(tabAlarm);
        lblOtF->setObjectName("lblOtF");

        formAlarm->setWidget(5, QFormLayout::LabelRole, lblOtF);

        spinOtFault = new QDoubleSpinBox(tabAlarm);
        spinOtFault->setObjectName("spinOtFault");
        spinOtFault->setDecimals(1);
        spinOtFault->setMinimum(-100.000000000000000);
        spinOtFault->setMaximum(500.000000000000000);

        formAlarm->setWidget(5, QFormLayout::FieldRole, spinOtFault);

        lblLt = new QLabel(tabAlarm);
        lblLt->setObjectName("lblLt");

        formAlarm->setWidget(6, QFormLayout::LabelRole, lblLt);

        spinLtWarn = new QDoubleSpinBox(tabAlarm);
        spinLtWarn->setObjectName("spinLtWarn");
        spinLtWarn->setDecimals(1);
        spinLtWarn->setMinimum(-100.000000000000000);
        spinLtWarn->setMaximum(500.000000000000000);

        formAlarm->setWidget(6, QFormLayout::FieldRole, spinLtWarn);

        lblLtF = new QLabel(tabAlarm);
        lblLtF->setObjectName("lblLtF");

        formAlarm->setWidget(7, QFormLayout::LabelRole, lblLtF);

        spinLtFault = new QDoubleSpinBox(tabAlarm);
        spinLtFault->setObjectName("spinLtFault");
        spinLtFault->setDecimals(1);
        spinLtFault->setMinimum(-100.000000000000000);
        spinLtFault->setMaximum(500.000000000000000);

        formAlarm->setWidget(7, QFormLayout::FieldRole, spinLtFault);

        tabWidget->addTab(tabAlarm, QString());
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(200, 470, 240, 28));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "\350\256\276\345\244\207\347\274\226\350\276\221", nullptr));
        lblDevId->setText(QCoreApplication::translate("Dialog", "\350\256\276\345\244\207 ID\357\274\210\344\270\273\351\224\256\357\274\211", nullptr));
        lblDevIdValue->setText(QCoreApplication::translate("Dialog", "-", nullptr));
        lblDevIdValue->setProperty("class", QVariant(QCoreApplication::translate("Dialog", "valueText", nullptr)));
        lblName->setText(QCoreApplication::translate("Dialog", "\350\256\276\345\244\207\345\220\215\347\247\260", nullptr));
        lblModel->setText(QCoreApplication::translate("Dialog", "\347\202\271\350\241\250\346\250\241\346\235\277\357\274\210\345\236\213\345\217\267\357\274\211", nullptr));
        cmbModel->setItemText(0, QCoreApplication::translate("Dialog", "BMU-LFP-208S", nullptr));
        cmbModel->setItemText(1, QCoreApplication::translate("Dialog", "BMU-LFP-160S", nullptr));
        cmbModel->setItemText(2, QCoreApplication::translate("Dialog", "BMU-LFP-104S", nullptr));

        lblUnit->setText(QCoreApplication::translate("Dialog", "\346\211\200\345\261\236\345\202\250\350\203\275\345\215\225\345\205\203\357\274\210PCS\357\274\211", nullptr));
        cmbUnit->setItemText(0, QCoreApplication::translate("Dialog", "1", nullptr));
        cmbUnit->setItemText(1, QCoreApplication::translate("Dialog", "2", nullptr));
        cmbUnit->setItemText(2, QCoreApplication::translate("Dialog", "3", nullptr));
        cmbUnit->setItemText(3, QCoreApplication::translate("Dialog", "4", nullptr));

        lblSlave->setText(QCoreApplication::translate("Dialog", "Modbus \344\273\216\347\253\231\345\234\260\345\235\200", nullptr));
        lblEnabled->setText(QCoreApplication::translate("Dialog", "\351\207\207\351\233\206\347\212\266\346\200\201", nullptr));
        chkEnabled->setText(QCoreApplication::translate("Dialog", "\345\220\257\347\224\250\357\274\210\345\201\234\347\224\250\345\210\231\344\270\215\345\217\202\344\270\216\350\275\256\350\257\242\357\274\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabBasic), QCoreApplication::translate("Dialog", "\345\237\272\346\234\254 / \351\200\232\350\256\257", nullptr));
        lblRatedV->setText(QCoreApplication::translate("Dialog", "\351\242\235\345\256\232\347\224\265\345\216\213 (V)", nullptr));
        lblCapacity->setText(QCoreApplication::translate("Dialog", "\351\242\235\345\256\232\345\256\271\351\207\217 (kWh)", nullptr));
        lblChgI->setText(QCoreApplication::translate("Dialog", "\351\242\235\345\256\232\345\205\205\347\224\265\347\224\265\346\265\201 (A)", nullptr));
        lblDisI->setText(QCoreApplication::translate("Dialog", "\351\242\235\345\256\232\346\224\276\347\224\265\347\224\265\346\265\201 (A)", nullptr));
        lblSerial->setText(QCoreApplication::translate("Dialog", "\347\224\265\350\212\257\344\270\262\350\201\224\346\225\260 (1PnS)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRated), QCoreApplication::translate("Dialog", "\351\242\235\345\256\232\345\217\202\346\225\260", nullptr));
        lblOv->setText(QCoreApplication::translate("Dialog", "\350\277\207\345\216\213\351\242\204\350\255\246 (V)", nullptr));
        lblOvF->setText(QCoreApplication::translate("Dialog", "\350\277\207\345\216\213\346\225\205\351\232\234 (V)", nullptr));
        lblUv->setText(QCoreApplication::translate("Dialog", "\346\254\240\345\216\213\351\242\204\350\255\246 (V)", nullptr));
        lblUvF->setText(QCoreApplication::translate("Dialog", "\346\254\240\345\216\213\346\225\205\351\232\234 (V)", nullptr));
        lblOt->setText(QCoreApplication::translate("Dialog", "\350\277\207\346\270\251\351\242\204\350\255\246 (\302\260C)", nullptr));
        lblOtF->setText(QCoreApplication::translate("Dialog", "\350\277\207\346\270\251\346\225\205\351\232\234 (\302\260C)", nullptr));
        lblLt->setText(QCoreApplication::translate("Dialog", "\344\275\216\346\270\251\351\242\204\350\255\246 (\302\260C)", nullptr));
        lblLtF->setText(QCoreApplication::translate("Dialog", "\344\275\216\346\270\251\346\225\205\351\232\234 (\302\260C)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAlarm), QCoreApplication::translate("Dialog", "\345\221\212\350\255\246\345\256\232\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
