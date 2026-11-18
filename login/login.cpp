#include "login.h"
#include "ui_login.h"
#include "session.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFile>
#include <QGuiApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QScreen>
#include <QSettings>

namespace {

// 演示账号表：账号名 -> 固定密码 + 该账号真实角色。
// 角色必须与下拉框选择一致，避免“用操作员账号冒充管理员”。
struct Account {
    const char *user;
    const char *password;
    Session::Role role;
};

const Account kAccounts[] = {
    {"operator", "123456", Session::Role::Operator},
    {"engineer", "123456", Session::Role::Engineer},
    {"admin",    "123456", Session::Role::Admin},
};

// QSettings 的 key 集中放在这里，登录页与以后“退出登录”共用
const char *kKeyUser     = "login/user";
const char *kKeyRole     = "login/role";
const char *kKeyRemember = "login/remember";

} // namespace

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // 不显示右上角的 “?” 帮助按钮，登录框只需要关闭
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(440, 560);

    QFile qss(QStringLiteral(":/style/login.qss"));
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(qss.readAll()));
        qss.close();
    }

    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    // 回车即登录：密码框和按钮都接一次，鼠标点不点都能进
    connect(ui->editPwd, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
    connect(ui->editUser, &QLineEdit::returnPressed, this, [this] {
        ui->editPwd->setFocus();
    });

    loadRemembered();

    // 无父窗口时居中到屏幕，避免对话框跑到左上角
    if (!parent) {
        const QRect screen = QGuiApplication::primaryScreen()->availableGeometry();
        move(screen.center() - rect().center());
    }
    ui->editUser->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLoginClicked()
{
    const QString user = ui->editUser->text().trimmed();
    const QString password = ui->editPwd->text();

    if (user.isEmpty()) {
        showError(QStringLiteral("请输入用户名"));
        ui->editUser->setFocus();
        return;
    }
    if (password.isEmpty()) {
        showError(QStringLiteral("请输入密码"));
        ui->editPwd->setFocus();
        return;
    }

    // 账号不区分大小写，密码严格匹配（这里只做演示用的明文字典）
    const Account *hit = nullptr;
    for (const Account &account : kAccounts) {
        if (user.compare(QLatin1String(account.user), Qt::CaseInsensitive) == 0) {
            hit = &account;
            break;
        }
    }
    if (!hit || password != QLatin1String(hit->password)) {
        showError(QStringLiteral("用户名或密码错误"));
        ui->editPwd->clear();
        ui->editPwd->setFocus();
        return;
    }

    // 第二步校验：账号自带的角色必须与下拉框选中的角色一致
    const Session::Role picked = static_cast<Session::Role>(ui->comboRole->currentIndex());
    if (picked != hit->role) {
        showError(QStringLiteral("所选角色与该账号权限不符"));
        ui->comboRole->setFocus();
        return;
    }

    Session::instance()->login(hit->user, hit->role);
    saveRemembered();
    accept();
}

void LoginDialog::loadRemembered()
{
    QSettings settings;
    const bool remember = settings.value(QLatin1String(kKeyRemember), false).toBool();
    if (!remember) {
        return;
    }
    ui->editUser->setText(settings.value(QLatin1String(kKeyUser)).toString());
    ui->comboRole->setCurrentIndex(settings.value(QLatin1String(kKeyRole), 0).toInt());
    ui->chkRemember->setChecked(true);
}

void LoginDialog::saveRemembered()
{
    QSettings settings;
    if (ui->chkRemember->isChecked()) {
        settings.setValue(QLatin1String(kKeyRemember), true);
        settings.setValue(QLatin1String(kKeyUser), ui->editUser->text().trimmed());
        settings.setValue(QLatin1String(kKeyRole), ui->comboRole->currentIndex());
    } else {
        // 不记住时把旧值清掉，下次启动是干净状态
        settings.remove(QLatin1String(kKeyRemember));
        settings.remove(QLatin1String(kKeyUser));
        settings.remove(QLatin1String(kKeyRole));
    }
}

void LoginDialog::showError(const QString &msg)
{
    ui->lblError->setText(msg);
    ui->lblError->setVisible(true);
}
