#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

/**
 * @brief 登录对话框：用户名 + 密码 + 角色三级校验。
 *
 * 校验通过才 accept()；调用方用 exec() == QDialog::Accepted 判断是否可以进入主界面。
 */
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void onLoginClicked();

private:
    void loadRemembered();
    void saveRemembered();
    void showError(const QString &msg);

    Ui::LoginDialog *ui;
};

#endif // LOGIN_H
