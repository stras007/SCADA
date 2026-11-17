#include "projectconfig.h"
#include <QDebug>

// 静态单例指针初始化为空
ProjectConfig* ProjectConfig::m_instance = nullptr;

ProjectConfig* ProjectConfig::instance()
{
    // 懒加载：第一次调用才new对象
    if(m_instance == nullptr)
    {
        // parent=nullptr，无父对象的单例常驻到进程退出，由进程回收
        m_instance = new ProjectConfig(nullptr);
    }
    return m_instance;
}

/**
 * @brief ClusterAlarm转json对象
 */
QJsonObject ClusterAlarm::toJson() const
{
    QJsonObject obj;
    obj["ovWarn"]  = ovWarn;
    obj["ovFault"] = ovFault;
    obj["uvWarn"]  = uvWarn;
    obj["uvFault"] = uvFault;
    obj["otWarn"]  = otWarn;
    obj["otFault"] = otFault;
    obj["ltWarn"]  = ltWarn;
    obj["ltFault"] = ltFault;
    return obj;
}

/**
 * @brief 从json对象生成ClusterAlarm结构体
 */
ClusterAlarm ClusterAlarm::fromJson(const QJsonObject &obj)
{
    ClusterAlarm a;
    a.ovWarn  = obj["ovWarn"].toDouble();
    a.ovFault = obj["ovFault"].toDouble();
    a.uvWarn  = obj["uvWarn"].toDouble();
    a.uvFault = obj["uvFault"].toDouble();
    a.otWarn  = obj["otWarn"].toDouble();
    a.otFault = obj["otFault"].toDouble();
    a.ltWarn  = obj["ltWarn"].toDouble();
    a.ltFault = obj["ltFault"].toDouble();
    return a;
}

/**
 * @brief ClusterItem结构体转json
 */
QJsonObject ClusterItem::toJson() const
{
    QJsonObject obj;
    obj["alarm"] = alarm.toJson();
    obj["deviceId"] = deviceId;
    obj["name"] = name;
    obj["model"] = model;
    obj["pcsUnit"] = pcsUnit;
    obj["slaveId"] = slaveId;
    obj["enabled"] = enabled;
    obj["ratedVoltage"] = ratedVoltage;
    obj["ratedCapacity"] = ratedCapacity;
    obj["ratedChgCurrent"] = ratedChgCurrent;
    obj["ratedDisCurrent"] = ratedDisCurrent;
    obj["cellSerial"] = cellSerial;
    return obj;
}

/**
 * @brief 从json对象解析ClusterItem
 */
ClusterItem ClusterItem::fromJson(const QJsonObject &obj)
{
    ClusterItem item;
    item.alarm = ClusterAlarm::fromJson(obj["alarm"].toObject());
    item.deviceId = obj["deviceId"].toInt();
    item.name = obj["name"].toString();
    item.model = obj["model"].toString();
    item.pcsUnit = obj["pcsUnit"].toInt();
    item.slaveId = obj["slaveId"].toInt();
    item.enabled = obj["enabled"].toBool();
    item.ratedVoltage = obj["ratedVoltage"].toDouble();
    item.ratedCapacity = obj["ratedCapacity"].toDouble();
    item.ratedChgCurrent = obj["ratedChgCurrent"].toDouble();
    item.ratedDisCurrent = obj["ratedDisCurrent"].toDouble();
    item.cellSerial = obj["cellSerial"].toInt();
    return item;
}

/**
 * @brief 私有构造
 */
ProjectConfig::ProjectConfig(QObject *parent)
    : QObject(parent)
{

}

void ProjectConfig::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

QString ProjectConfig::filePath() const
{
    return m_filePath;
}

/**
 * @brief 从文件加载配置到内存
 * 步骤：打开文件→读取字节→解析json→赋值到内存成员
 */
bool ProjectConfig::loadFromFile()
{
    QFile file(m_filePath);
    // 只读文本模式打开
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "打开配置文件失败:" << file.errorString();
        return false;
    }
    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &err);
    // json语法错误
    if (err.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON解析错误:" << err.errorString();
        return false;
    }
    // 根节点必须是对象，不能是数组
    if (!doc.isObject())
    {
        qDebug() << "JSON根不是对象";
        return false;
    }
    // 解析到内存变量
    fromJsonObject(doc.object());
    return true;
}

/**
 * @brief 将内存全部配置覆盖写回磁盘文件
 */
bool ProjectConfig::saveToFile()
{
    QFile file(m_filePath);
    // WriteOnly会直接截断覆盖原有文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "写入配置文件失败:" << file.errorString();
        return false;
    }
    QJsonObject root = toJsonObject();
    QJsonDocument doc(root);
    // Indented：格式化带缩进，方便人阅读；Compact为压缩一行
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Indented);
    file.write(jsonBytes);
    file.close();
    return true;
}

/**
 * @brief 内存全部数据组装为根QJsonObject
 */
QJsonObject ProjectConfig::toJsonObject() const
{
    QJsonObject root;
    QJsonArray arrClusters;
    // 遍历簇列表，转为json数组
    for(const auto& item : clusters)
    {
        arrClusters.append(item.toJson());
    }
    root["clusters"] = arrClusters;
    root["host"] = host;
    root["port"] = port;
    root["pcsSlave"] = pcsSlave;
    root["nextDeviceId"] = nextDeviceId;
    root["version"] = version;
    return root;
}

/**
 * @brief 从根json对象刷新内存，原有clusters会被clear清空
 */
void ProjectConfig::fromJsonObject(const QJsonObject &rootObj)
{
    clusters.clear(); // 清空旧列表

    host = rootObj["host"].toString();
    port = rootObj["port"].toInt();
    pcsSlave = rootObj["pcsSlave"].toInt();
    nextDeviceId = rootObj["nextDeviceId"].toInt();
    version = rootObj["version"].toInt();

    QJsonArray arr = rootObj["clusters"].toArray();
    // 遍历clusters数组，逐个解析ClusterItem存入list
    for(const auto& val : arr)
    {
        QJsonObject obj = val.toObject();
        ClusterItem it = ClusterItem::fromJson(obj);
        clusters.append(it);
    }
}