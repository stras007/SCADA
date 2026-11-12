#include "modbusdebug.h"
#include "ui_modbusdebug.h"

ModbusDebug::ModbusDebug(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModbusDebug)
{
    ui->setupUi(this);
}

ModbusDebug::~ModbusDebug()
{
    delete ui;
}
