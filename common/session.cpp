#include "session.h"

Session *Session::m_instance = nullptr;

Session::Session(QObject *parent)
    : QObject(parent)
{
}

Session *Session::instance()
{
    // 首次调用才创建，进程退出由 Qt 父子关系之外的静态指针持有；
    // 登录页与主窗口都拿到同一份状态，不额外传参。
    if (!m_instance) {
        m_instance = new Session;
    }
    return m_instance;
}

void Session::login(const QString &userName, Role role)
{
    m_userName = userName;
    m_role = role;
    emit sessionChanged();
}

void Session::logout()
{
    m_userName.clear();
    m_role = Role::Operator;
    emit sessionChanged();
}

QString Session::roleName() const
{
    // 与登录页下拉框顺序保持一致：0 操作员 / 1 工程师 / 2 管理员
    switch (m_role) {
    case Role::Operator:
        return QStringLiteral("操作员");
    case Role::Engineer:
        return QStringLiteral("工程师");
    case Role::Admin:
        return QStringLiteral("管理员");
    }
    return QStringLiteral("操作员");
}

bool Session::canControl() const
{
    return m_role == Role::Engineer || m_role == Role::Admin;
}

bool Session::canConfigure() const
{
    return canControl();
}

bool Session::canDebug() const
{
    return canControl();
}

bool Session::canSystemSetting() const
{
    return m_role == Role::Admin;
}
