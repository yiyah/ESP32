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
#include "hs_err.h"
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
#define REG_DIS_AUTO_SLEEP      0xFE        /*!< 0: 使能自动进入 low power mode
                                                !0: 禁止进入 low power mode */

/**********************
 *      TYPEDEFS
 **********************/

/* 连续动作配置选项: REG_MOTION_MASK */
typedef enum {
    MOTION_NONE             = 0x00,         /*!< 禁止连续动作 */
    MOTION_DOUBLE_CLICK     = 0x01,         /*!< bit0: 双击 */
    MOTION_LEFT_RIGHT       = 0x02,         /*!< bit1: 左右滑动 */
    MOTION_UP_DOWN          = 0x04,         /*!< bit2: 上下滑动 */
    MOTION_ALL_ENABLE       = 0x07,         /*!< bit0~bit2: 启用所有连续动作 */
} cst816_motion_t;

/* REG_IRQ_CTL */
#define IRQ_CTL_ONCEWLP_POS     0
#define IRQ_CTL_ONCEWLP_MASK    (0x1U << IRQ_CTL_ONCEWLP_POS)
#define IRQ_CTL_ONCEWLP         IRQ_CTL_ONCEWLP_MASK

#define IRQ_CTL_ENMOTION_POS    4
#define IRQ_CTL_ENMOTION_MASK   (0x1U << IRQ_CTL_ENMOTION_POS)
#define IRQ_CTL_ENMOTION        IRQ_CTL_ENMOTION_MASK

#define IRQ_CTL_ENCHANGE_POS    5
#define IRQ_CTL_ENCHANGE_MASK   (0x1U << IRQ_CTL_ENCHANGE_POS)
#define IRQ_CTL_ENCHANGE        IRQ_CTL_ENCHANGE_MASK

#define IRQ_CTL_ENTOUCH_POS     6
#define IRQ_CTL_ENTOUCH_MASK    (0x1U << IRQ_CTL_ENTOUCH_POS)
#define IRQ_CTL_ENTOUCH         IRQ_CTL_ENTOUCH_MASK

#define IRQ_CTL_ENTEST_POS      7
#define IRQ_CTL_ENTEST_MASK     (0x1U << IRQ_CTL_ENTEST_POS)
#define IRQ_CTL_ENTEST          IRQ_CTL_ENTEST_MASK

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void cst816_init(void);
void cst816_reset(void);
hs_err_t cst816_get_touch_point(uint16_t* x, uint16_t* y);
uint8_t cst816_get_touch_point_num(void);
uint8_t cst816_get_chip_id(void);
hs_err_t cst816_enable_motion(cst816_motion_t motion);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CST816_H */
