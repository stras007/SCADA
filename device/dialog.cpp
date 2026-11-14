#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setConfig(const ClusterItem &item)
{
    // ===== 基本通讯tab =====
    ui->lblDevIdValue->setText(QString::number(item.deviceId));
    ui->editName->setText(item.name);
    ui->cmbModel->setCurrentText(item.model);
    ui->cmbUnit->setCurrentText(QString::number(item.pcsUnit));
    ui->spinSlave->setValue(item.slaveId);
    ui->chkEnabled->setChecked(item.enabled);

    // ===== 额定参数tab =====
    ui->spinRatedV->setValue(item.ratedVoltage);
    ui->spinCapacity->setValue(item.ratedCapacity);
    ui->spinChgI->setValue(item.ratedChgCurrent);
    ui->spinDisI->setValue(item.ratedDisCurrent);
    ui->spinSerial->setValue(item.cellSerial);

    // ===== 告警定值tab =====
    ui->spinOvWarn->setValue(item.alarm.ovWarn);
    ui->spinOvFault->setValue(item.alarm.ovFault);
    ui->spinUvWarn->setValue(item.alarm.uvWarn);
    ui->spinUvFault->setValue(item.alarm.uvFault);
    ui->spinOtWarn->setValue(item.alarm.otWarn);
    ui->spinOtFault->setValue(item.alarm.otFault);
    ui->spinLtWarn->setValue(item.alarm.ltWarn);
    ui->spinLtFault->setValue(item.alarm.ltFault);
}

ClusterItem Dialog::config() const
{
    ClusterItem item;

    // 基本通讯
    item.deviceId = ui->lblDevIdValue->text().toInt(); // label仅展示，不可编辑
    item.name = ui->editName->text().trimmed();
    item.model = ui->cmbModel->currentText();
    item.pcsUnit = ui->cmbUnit->currentText().toInt();
    item.slaveId = ui->spinSlave->value();
    item.enabled = ui->chkEnabled->isChecked();

    // 额定参数
    item.ratedVoltage = ui->spinRatedV->value();
    item.ratedCapacity = ui->spinCapacity->value();
    item.ratedChgCurrent = ui->spinChgI->value();
    item.ratedDisCurrent = ui->spinDisI->value();
    item.cellSerial = ui->spinSerial->value();

    // 告警阈值
    item.alarm.ovWarn = ui->spinOvWarn->value();
    item.alarm.ovFault = ui->spinOvFault->value();
    item.alarm.uvWarn = ui->spinUvWarn->value();
    item.alarm.uvFault = ui->spinUvFault->value();
    item.alarm.otWarn = ui->spinOtWarn->value();
    item.alarm.otFault = ui->spinOtFault->value();
    item.alarm.ltWarn = ui->spinLtWarn->value();
    item.alarm.ltFault = ui->spinLtFault->value();

    return item;
}
