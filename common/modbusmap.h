#ifndef MODBUSMAP_H
#define MODBUSMAP_H

/**
 * 寄存器点表 —— 上位机与模拟器的单一数据来源
 * ------------------------------------------------------------------
 * 模拟器 bms_simulator.pro 通过 INCLUDEPATH 直接引用本文件，
 * 改动点表两边同时生效，杜绝双端不一致。
 *
 * 地址规则：每个设备（电池簇 / PCS）各占一个 Modbus 从站地址，
 * 寄存器布局统一为 0x0100 起的 20 个寄存器（模组电压区另加 0x0200 起 16 个）。
 */

// ---------- 电池簇数据区（每个簇从站布局相同） ----------
namespace ModbusMap {
constexpr int RegBase  = 0x0100;   // 簇数据区起始地址
constexpr int RegCount = 20;       // 簇数据区长度
constexpr int ModBase  = 0x0200;   // 模组电压区起始地址
constexpr int ModCount = 16;       // 模组数量
// 相对 RegBase 的字段偏移
constexpr int OffVoltage   = 0;    // 簇电压 0.1V
constexpr int OffCurrent   = 2;    // 电流 0.1A 有符号（正=充电）
constexpr int OffSoc       = 4;    // SOC 1%
constexpr int OffSoh       = 5;    // SOH 1%
constexpr int OffMaxTemp   = 6;    // 最高温 1°C 有符号
constexpr int OffMinTemp   = 7;    // 最低温 1°C
constexpr int OffMaxCellV  = 8;    // 最高单体电压 mV
constexpr int OffMinCellV  = 9;    // 最低单体电压 mV
constexpr int OffCycles    = 10;   // 循环次数
constexpr int OffStatus    = 12;   // 状态字：bit0运行 bit1充电 bit2放电 bit3告警 bit4故障
constexpr int OffAlarmCnt  = 14;   // 当前告警数
constexpr int OffChgEnergy = 16;   // 累计充电量 0.1kWh
constexpr int OffDisEnergy = 18;   // 累计放电量 0.1kWh
}

// ---------- PCS 逆变器数据区（独立从站地址） ----------
namespace PcsMap {
constexpr int RegBase  = 0x0100;   // PCS 数据区起始地址
constexpr int RegCount = 20;       // PCS 数据区长度
// 相对 RegBase 的字段偏移
constexpr int OffPower     = 0;    // 交流有功功率 0.1kW 有符号（正=放电）
constexpr int OffReactive  = 2;    // 交流无功功率 0.1kvar
constexpr int OffAcVoltage = 4;    // 交流线电压 0.1V
constexpr int OffFreq      = 5;    // 电网频率 0.01Hz
constexpr int OffDcVoltage = 6;    // 直流侧电压 0.1V
constexpr int OffDcCurrent = 7;    // 直流侧电流 0.1A 有符号（正=充电）
constexpr int OffTemp      = 8;    // 逆变器温度 1°C 有符号
constexpr int OffStatus    = 10;   // 状态字：bit0待机 bit1并网运行 bit2故障 bit3限功率
constexpr int OffDayChg    = 12;   // 日充电量 0.1kWh（跨天自动清零）
constexpr int OffDayDis    = 14;   // 日放电量 0.1kWh
constexpr int OffTotalChg  = 16;   // 累计充电量 0.1kWh
constexpr int OffTotalDis  = 18;   // 累计放电量 0.1kWh
}

#endif // MODBUSMAP_H