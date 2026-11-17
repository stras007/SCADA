#ifndef MODBUSMANAGER_H
#define MODBUSMANAGER_H

#include <QObject>
#include <QModbusTcpClient>
#include <QTimer>
#include "projectconfig.h"

/**
 * @brief 越限告警位定义：一个 quint16 装 8 种状态，位运算判断
 */
namespace AlarmBits {
    constexpr quint16 OvWarn  = 0x0001, OvFault  = 0x0002;
    constexpr quint16 UvWarn  = 0x0004, UvFault  = 0x0008;
    constexpr quint16 OtWarn  = 0x0010, OtFault  = 0x0020;
    constexpr quint16 LtWarn  = 0x0040, LtFault  = 0x0080;

// 位 → 可读文本：0x0021 → "过压预警/过温故障"
    inline QString text(quint16 f)
    {
        QStringList s;
        if (f & OvWarn)  s << QStringLiteral("过压预警");
        if (f & OvFault) s << QStringLiteral("过压故障");
        if (f & UvWarn)  s << QStringLiteral("欠压预警");
        if (f & UvFault) s << QStringLiteral("欠压故障");
        if (f & OtWarn)  s << QStringLiteral("过温预警");
        if (f & OtFault) s << QStringLiteral("过温故障");
        if (f & LtWarn)  s << QStringLiteral("低温预警");
        if (f & LtFault) s << QStringLiteral("低温故障");
        return s.join(QStringLiteral("/"));
    }
}

/** 单簇实时数据（寄存器原始值 + 越限判定结果，界面层负责换算显示） */
struct ClusterData {
    int deviceId = 0;    // 组态主键：改从站地址不丢绑定
    int slaveId = 0;
    QString name;
    int voltage = 0;    // 0.1V
    int current = 0;    // 0.1A（有符号，正=充电）
    int soc = 0;        // 1%
    int soh = 0;        // 1%
    int maxTemp = 0;    // 1°C（有符号）
    int minTemp = 0;
    int maxCellV = 0;   // mV
    int minCellV = 0;   // mV
    int statusWord = 0; // 位定义见 ModbusMap::OffStatus
    quint16 alarmFlags = 0;  // 越限监视结果，位定义见 AlarmBits
};

/** PCS 逆变器实时数据（寄存器原始值，界面层负责换算显示） */
struct PcsData {
    int power = 0;      // 0.1kW（有符号，正=放电）
    int acVoltage = 0;  // 0.1V
    int freq = 0;       // 0.01Hz
    int dcVoltage = 0;  // 0.1V
    int dcCurrent = 0;  // 0.1A（有符号，正=充电）
    int temp = 0;       // 1°C
    int statusWord = 0; // 位定义见 PcsMap::OffStatus
    int dayChg = 0;     // 日充电量 0.1kWh
    int dayDis = 0;     // 日放电量 0.1kWh
    int totalChg = 0;   // 累计充电量 0.1kWh
    int totalDis = 0;   // 累计放电量 0.1kWh
};

class ModbusManager : public QObject
{
    Q_OBJECT

private:
    explicit ModbusManager(QObject *parent = nullptr);
    ~ModbusManager() override;
    ModbusManager(const ModbusManager &) = delete;         // 禁止复制构造
    ModbusManager &operator=(const ModbusManager &) = delete; // 禁止赋值拷贝
    QModbusTcpClient *client;    // Modbus TCP 客户端底层对象
    QTimer *pollTimer;
    bool waiting = false;        // 忙等标记
    QList<ClusterItem> clusters;
    int pcsSlave = 0;            // PCS从站地址，0代表不开启PCS轮询
    int pollIndex = 0;           // 轮询游标，标记下一个要访问的设备下标
    QHash<int, quint16> alarmState;  // deviceId -> 上一次告警掩码，用于边沿检测
    QHash<int, bool> onlineState;    // deviceId -> 在线状态，用于在线/离线边沿检测

public:
    static ModbusManager* instance();
    void onStateChanged(QModbusDevice::State st);
    void setConfig(const ProjectConfig &cfg);
    void connectTo(const QString &host, int port);
    bool isConnected();
    void disconnectDevice();
    void handlePollReply(QModbusReply* reply, ClusterItem item, bool isPcs);
    quint16 checkLimits(const ClusterAlarm &alarm, double voltV, int maxTemp);

private slots:
    void pollTick();

signals:
    void logMessage(const QString& msg);
    void connectionChanaged(QModbusDevice::State st);
    void clusterUpdated(const ClusterData& data);
    void pcsUpdated(const PcsData& data);
    void configApplied(const QList<ClusterItem>& clusters);
};

#endif // MODBUSMANAGER_H
