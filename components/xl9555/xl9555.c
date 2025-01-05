#include "driver/gpio.h"
#include "esp_log.h"
#include "../iic/iic.h"
#include "xl9555.h"

/* Define XL9555 HW */
#define XL9555_GPIO_INT_PIN     GPIO_NUM_40
#define XL9555_IIC_ADDR         (0x20u)

/* Define XL9555 register */
#define XL9555_INPUT_PORT0_REG          (0U)      /* 输入寄存器0地址 */
#define XL9555_INPUT_PORT1_REG          (1U)      /* 输入寄存器1地址 */
#define XL9555_OUTPUT_PORT0_REG         (2U)      /* 输出寄存器0地址 */
#define XL9555_OUTPUT_PORT1_REG         (3U)      /* 输出寄存器1地址 */
#define XL9555_INVERSION_PORT0_REG      (4U)      /* 极性反转寄存器0地址 */
#define XL9555_INVERSION_PORT1_REG      (5U)      /* 极性反转寄存器1地址 */
#define XL9555_CONFIG_PORT0_REG         (6U)      /* 方向配置寄存器0地址 */
#define XL9555_CONFIG_PORT1_REG         (7U)      /* 方向配置寄存器1地址 */

/**
 * @brief 
 * 
 * @param pin 
 * @param state 
 *      @arg 0: low level
 *      @arg 1: high level
 */
void XL9555_Write_pin(uint16_t pin, uint8_t state)
{
    uint8_t pins_state = 0x0;
    uint8_t reg = 0x0;

    reg = (pin & IO_IN_HIG_REG_MASK)
          ? XL9555_INPUT_PORT1_REG
          : XL9555_INPUT_PORT0_REG;
    IIC_Read_Bytes(I2C_NUM_0,
                   XL9555_IIC_ADDR, reg,
                   &pins_state, 1);

    pins_state = (0 == state)
                 ? pins_state & ~(pin & 0xFF)
                 : pins_state | (pin & 0xFF);
    IIC_Write_Bytes(I2C_NUM_0,
                    XL9555_IIC_ADDR, reg,
                    &pins_state, 1);
}

uint8_t XL9555_Read_pin(uint16_t pin)
{
    uint8_t data = 0x0;
    uint8_t reg = 0x0;

    reg = (pin & IO_IN_HIG_REG_MASK)
          ? XL9555_INPUT_PORT1_REG
          : XL9555_INPUT_PORT0_REG;
    IIC_Read_Bytes(I2C_NUM_0,
                   XL9555_IIC_ADDR, reg,
                   &data, 1);

    return (data & (pin & 0xFF));
}

/**
 * @brief 配置 XL9555 的 GPIO 端口的输入输出模式
 * @param pin: GPIO 端口
 * @param direction: input or output
 *      @arg 0: output mode
 *      @arg 1: input mode (default)
 */
void XL9555_Config_GPIO(uint16_t pin, XL9555_IO_DIRECTION direction)
{
    uint8_t pins_state = 0x0;
    uint8_t reg = 0x0;

    reg = (pin & IO_IN_HIG_REG_MASK)
          ? XL9555_CONFIG_PORT1_REG
          : XL9555_CONFIG_PORT0_REG;
    IIC_Read_Bytes(I2C_NUM_0,
                   XL9555_IIC_ADDR, reg,
                   &pins_state, 1);
    ESP_LOGW("XL9555", "pins_state: %d", pins_state);
    pins_state = (XL9555_IO_DIR_OUTPUT == direction)
                 ? pins_state & ~(pin & 0xFF)
                 : pins_state | (pin & 0xFF);
    IIC_Write_Bytes(I2C_NUM_0,
                    XL9555_IIC_ADDR, reg,
                    &pins_state, 1);
}

/**
 * 当输入模式的IO口发生变化时，INT_PIN 会被拉低。
 * 当中断有效后，必须对 XL9555 进行读取操作，否则中断会一直保持有效。
 */
void XL9555_Init(void)
{
    gpio_config_t io_conf = {0};

    io_conf.pin_bit_mask = (1ULL << XL9555_GPIO_INT_PIN);
    io_conf.mode         = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en   = GPIO_PULLUP_ENABLE;
    io_conf.intr_type    = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
}
