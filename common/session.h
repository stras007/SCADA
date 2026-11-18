#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>

/**
 * @brief 全局登录态：保存当前用户与角色，并对外提供权限判定。
 *
 * 界面里只问 “能不能”，不写死角色名：
 *   if (Session::instance()->canDebug()) ...
 * 这样以后加角色（比如只读访客）只改这一个文件。
 */
class Session : public QObject
{
    Q_OBJECT
public:
    enum class Role {
        Operator = 0,  // 操作员：只读监控
        Engineer = 1,  // 工程师：监控 + 设备组态 + 通讯调试
        Admin    = 2   // 管理员：工程师权限 + 系统设置
    };
    Q_ENUM(Role)

    static Session *instance();

    void login(const QString &userName, Role role);
    void logout();

    bool isLoggedIn() const { return !m_userName.isEmpty(); }
    QString userName() const { return m_userName; }
    Role role() const { return m_role; }
    QString roleName() const;

    bool canViewMonitor() const { return true; }         // 所有角色
    bool canControl() const;                             // 下发控制：工程师 / 管理员
    bool canConfigure() const;                           // 设备组态：工程师 / 管理员
    bool canDebug() const;                               // 通讯调试：工程师 / 管理员
    bool canSystemSetting() const;                       // 系统设置：仅管理员

signals:
    void sessionChanged();

private:
    explicit Session(QObject *parent = nullptr);
    static Session *m_instance;

    QString m_userName;
    Role m_role = Role::Operator;
};

#endif // SESSION_H
