#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "session.h"
#include <QDebug>
#include <QLabel>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // client = new QModbusTcpClient(this);

    // // 设置 ip, port
    // client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QStringLiteral("127.0.0.1"));
    // client->setConnectionParameter(QModbusDevice::NetworkPortParameter, 1502);

    // client->setTimeout(1000);
    // client->setNumberOfRetries(3);
    // client->connectDevice();

    // // 链接
    // connect(client, &QModbusTcpClient::stateChanged, this, &MainWindow::onStateChanged);
    // connect(client, &QModbusClient::errorOccurred, this, [](QModbusDevice::Error e) {
    //     if (e != QModbusDevice::NoError)
    //         qWarning() << "modbus error:" << e;
    // });

    // 侧边栏与页面栈的联动只建立一次，必须放在构造函数里
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            ui->pageList, &QStackedWidget::setCurrentIndex);
    ui->listWidget->setCurrentRow(0);

    applyRolePermissions();
}

void MainWindow::applyRolePermissions()
{
    Session *session = Session::instance();

    // 侧边栏顺序：0 数据看板 / 1 设备组态 / 2 通讯调试
    // 操作员只能看数据，组态和调试属于工程师及以上权限
    struct NavRule {
        int row;
        bool allowed;
    };
    const NavRule rules[] = {
        {1, session->canConfigure()},
        {2, session->canDebug()},
    };
    for (const NavRule &rule : rules) {
        QListWidgetItem *item = ui->listWidget->item(rule.row);
        if (!item) {
            continue;
        }
        // 置灰但保留文字：用户知道有这个功能，只是当前角色进不去
        item->setFlags(rule.allowed ? (item->flags() | Qt::ItemIsEnabled)
                                    : (item->flags() & ~Qt::ItemIsEnabled));
        item->setToolTip(rule.allowed ? QString()
                                      : QStringLiteral("需要工程师或管理员权限"));
    }

    setWindowTitle(QStringLiteral("储能监控系统 · %1").arg(session->roleName()));

    // 状态栏常驻当前用户，切换账号时一眼能看出身份
    statusBar()->setSizeGripEnabled(false);
    auto *userLabel = new QLabel(
        QStringLiteral("当前用户：%1（%2）").arg(session->userName(), session->roleName()),
        this);
    userLabel->setObjectName(QStringLiteral("lblCurrentUser"));
    statusBar()->addPermanentWidget(userLabel);
}

void MainWindow::onStateChanged(QModbusDevice::State state) {
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "connected";

        QModbusDataUnit req(QModbusDataUnit::HoldingRegisters, 0x0100, 20);
        QModbusReply *reply = client->sendReadRequest(req, 1);
        if (!reply)
        {
            qDebug() << "发送读请求失败:" << client->errorString();
            return;
        }

        connect(reply, &QModbusReply::finished, this, &MainWindow::onBmsReplyFinished);
    }

    if (state == QModbusDevice::ClosingState) {
        qDebug() << "closing";
    }
}

void MainWindow::onBmsReplyFinished() {
    QModbusReply *reply = qobject_cast<QModbusReply*>(sender());
    if (!reply) return;

    if (reply->error() == QModbusDevice::NoError)
    {
        auto res = reply->result();
        quint16 uVol        = res.value(0);
        qint16  iCur        = (qint16)res.value(2);
        quint16 soc         = res.value(4);
        quint16 soh         = res.value(5);
        qint16 tMax         = (qint16)res.value(6);
        qint16 tMin         = (qint16)res.value(7);
        quint16 cellMaxV    = res.value(8);
        quint16 cellMinV    = res.value(9);
        quint16 cycle       = res.value(10);
        quint16 status      = res.value(12);
        quint16 alarmCnt    = res.value(14);
        quint16 chgTotal    = res.value(16);
        quint16 disTotal    = res.value(18);

        qDebug() << "\n==== BMS电池簇 ====";
        qDebug() << "簇电压:" << uVol * 0.1f << " V";
        qDebug() << "簇电流:" << iCur * 0.1f << " A";
        qDebug() << "SOC:" << soc << "%  SOH:" << soh << "%";
        qDebug() << "最高温:" << tMax << "℃  最低温:" << tMin << "℃";
        qDebug() << "最高单体电压:" << cellMaxV << "mV  最低单体:" << cellMinV << "mV";
        qDebug() << "循环次数:" << cycle;
        qDebug() << "状态字:" << QString("0x%1").arg(status,4,16,QLatin1Char('0'));
        qDebug() << "告警数量:" << alarmCnt;
        qDebug() << "累计充电:" << chgTotal * 0.1f << " kWh";
        qDebug() << "累计放电:" << disTotal * 0.1f << " kWh";
    }
    else
    {
        qDebug() << "读取错误:" << reply->errorString();
    }

    reply->deleteLater();
}

MainWindow::~MainWindow()
{
    // client 是 this 的子对象，要等到 ~QObject 销毁子对象时才被删。
    // 它的析构里会 close()，而 close() 同步发出 stateChanged，此时 MainWindow
    // 的派生部分早已析构完，Qt6 对成员函数连接会用 dynamic_cast 校验接收者类型，
    // 校验失败 → Q_ASSERT_X → abort() → 0xC0000409（"快速异常检测失败"）。
    // 关窗前掐断回调，避免析构期被信号回调到半析构的对象上。
    if (client)
        disconnect(client, nullptr, this, nullptr);

    delete ui;
}
