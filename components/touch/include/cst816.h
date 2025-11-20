/**
 * @file cst816.h
 *
 */

#ifndef CST816_H
#define CST816_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**
 * @brief CST816 触摸屏寄存器地址定义
 */
#define REG_GESTURE_ID          0x01        // 触摸屏中与手势识别
#define REG_FINGER_NUM          0x02        // 记录触摸手指数量
#define REG_XPOS_H              0x03        // X 坐标高 4 位相关的寄存器地址
#define REG_XPOS_L              0x04        // X 坐标低 8 位部分的寄存器地址
#define REG_YPOS_H              0x05        // Y 坐标高 4 位相关的寄存器地址
#define REG_YPOS_L              0x06        // Y 坐标低8位部分的寄存器地址
#define REG_CHIP_ID             0xA7        // 访问触摸屏芯片的唯一标识符寄存器的地址
#define REG_SLEEP_MODE          0xE5        // 控制触摸屏进入或退出睡眠模式的寄存器地址
#define REG_MOTION_MASK         0xEC        // 对某些运动相关操作的屏蔽或启用设置
#define REG_IRQ_PULSE_WIDTH     0xED        // 中断低脉冲宽度相关的寄存器地址
#define REG_NOR_SCAN_PER        0xEE        // 触摸屏正常扫描周期相关的寄存器地址
#define REG_MOTION_SL_ANGLE     0xEF        // 涉及到运动滑动角度相关
#define REG_LP_AUTO_WAKE_TIME   0xF4        // 长按自动唤醒时间
#define REG_LP_SCAN_TH          0xF5        // 触摸屏的长按扫描阈值
#define REG_LP_SCAN_WIN         0xF6        // 触摸屏的长按扫描窗口相关
#define REG_LP_SCAN_FREQ        0xF7        // 触摸屏的长按扫描频率
#define REG_LP_SCAN_IDAC        0xF8        // 长按扫描电流
#define REG_AUTO_SLEEP_TIME     0xF9        // 触摸屏自动进入睡眠模式的时间相关
#define REG_IRQ_CTL             0xFA        // 触摸屏的中断控制相关
#define REG_AUTO_RESET          0xFB        // 触摸屏自动复位相关
#define REG_LONG_PRESS_TIME     0xFC        // 触摸屏的长按时间
#define REG_IO_CTL              0xFD        // 触摸屏的输入输出控制
#define REG_DIS_AUTO_SLEEP      0xFE        // 禁止触摸屏自动进入睡眠模式

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CST816_H */
