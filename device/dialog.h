#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "deviceconfig.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    // 将ClusterItem填充到弹窗各个控件
    void setConfig(const ClusterItem &item);
    // 从弹窗UI读取数据，返回组装好的ClusterItem
    ClusterItem config() const;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
