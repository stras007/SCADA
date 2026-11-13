#ifndef PROJECTCONFIG_H
#define PROJECTCONFIG_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

    /**
 * @brief 越限定值（预警/故障两级，单位与工程量一致：V / °C）
 */
    struct ClusterAlarm
{
    double ovWarn = 760.0;    // 过压预警
    double ovFault = 780.0;   // 过压故障
    double uvWarn = 600.0;    // 欠压预警
    double uvFault = 580.0;   // 欠压故障（数值越低越严重）
    double otWarn = 45.0;     // 过温预警
    double otFault = 55.0;    // 过温故障
    double ltWarn = 5.0;      // 低温预警
    double ltFault = 0.0;     // 低温故障（数值越低越严重）

    QJsonObject toJson() const;
    static ClusterAlarm fromJson(const QJsonObject& obj);
};

/**
 * @brief 单台电池簇组态配置
 */
struct ClusterItem
{
    int deviceId = 0;                     // 主键：自增、稳定，永不复用
    QString name;                         // 显示名称
    QString model = "BMU-LFP-208S";       // 点表模板（设备型号）
    int pcsUnit = 1;                      // 所属储能单元（PCS编号）
    int slaveId = 1;                      // Modbus从站地址 1~247
    bool enabled = true;                  // false=停用，不采集
    double ratedVoltage = 720.0;          // 额定电压 V
    double ratedCapacity = 100.0;        // 额定容量 kWh
    double ratedChgCurrent = 125.0;      // 额定充电电流 A
    double ratedDisCurrent = 125.0;      // 额定放电电流 A
    int cellSerial = 208;                 // 电芯串联数

    ClusterAlarm alarm;                   // 告警阈值

    QJsonObject toJson() const;
    static ClusterItem fromJson(const QJsonObject& obj);
};

/**
 * @brief 项目全局配置管理类【单例模式】
 * 负责project_config.json加载、内存维护、保存回磁盘
 * 全局唯一实例，所有模块通过 ProjectConfig::instance() 获取对象
 * 注意：当前实现非线程安全，多线程访问需要外部加锁
 */
class ProjectConfig : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 获取全局单例实例
     * @return 唯一对象指针，不会返回nullptr
     */
    static ProjectConfig* instance();

    /**
     * @brief 设置配置json文件路径，程序启动必须调用一次
     * @param filePath 文件路径，如 "./project_config.json"
     */
    void setFilePath(const QString& filePath);

    /**
     * @brief 获取当前配置文件路径
     * @return 文件路径字符串
     */
    QString filePath() const;

    /**
     * @brief 从磁盘json文件加载配置到内存
     * @return true：加载成功；false：文件打开失败 / json解析出错
     */
    bool loadFromFile();

    /**
     * @brief 将内存中的全部配置覆盖写入磁盘json文件
     * @return true保存成功，false写入失败
     */
    bool saveToFile();

    // ========= 内存中的配置数据，外部直接读写 =========
    QList<ClusterItem> clusters;    // 全部电池簇列表
    QString host;                   // modbus服务端IP
    int port{1502};                 // modbus端口号，和样例json对齐1502
    int pcsSlave{11};               // PCS设备modbus从站号
    int nextDeviceId{1};            // 下一个新增设备分配的deviceId
    int version{1};                 // 配置文件版本号

    /**
     * @brief 将全部内存数据转为根QJsonObject
     * @return 根json对象
     */
    QJsonObject toJsonObject() const;

    /**
     * @brief 从根json对象解析，覆盖当前内存全部数据
     * @param rootObj json根对象
     */
    void fromJsonObject(const QJsonObject& rootObj);

    // 禁用拷贝构造、赋值运算符，禁止复制单例对象
    ProjectConfig(const ProjectConfig&) = delete;
    ProjectConfig& operator=(const ProjectConfig&) = delete;

private:
    /**
     * @brief 私有构造函数，外部禁止new，只能调用instance()
     * @param parent 父对象
     */
    explicit ProjectConfig(QObject *parent = nullptr);

    static ProjectConfig* m_instance;   // 单例静态实例指针

    QString m_filePath; // 配置文件路径
};

#endif // PROJECTCONFIG_H