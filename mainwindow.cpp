#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QModbusDataUnit>
#include <QModbusReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QModbusTcpClient(this);

    // 设置 ip, port
    client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QStringLiteral("127.0.0.1"));
    client->setConnectionParameter(QModbusDevice::NetworkPortParameter, 1502);

    client->setTimeout(1000);
    client->setNumberOfRetries(3);
    client->connectDevice();

    // 链接
    connect(client, &QModbusTcpClient::stateChanged, this, &MainWindow::onStateChanged);

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
    delete ui;
}
