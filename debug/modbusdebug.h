#ifndef MODBUSDEBUG_H
#define MODBUSDEBUG_H

#include <QWidget>

namespace Ui {
class ModbusDebug;
}

class ModbusDebug : public QWidget
{
    Q_OBJECT

public:
    explicit ModbusDebug(QWidget *parent = nullptr);
    ~ModbusDebug();

private:
    Ui::ModbusDebug *ui;
};

#endif // MODBUSDEBUG_H
