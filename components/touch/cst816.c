/**
 * @file cst816.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "port_cst816.h"
#include "cst816.h"
/*********************
 *      DEFINES
 *********************/
#define port_iic_read_register(reg, pdata) port_iic_read_from_device(reg, pdata, 1)
#define port_iic_write_register(reg, data) port_iic_write_to_device(reg, data, 1)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void cst816_init(void)
{
    // 初始化 IIC 和 GPIO

    port_iic_init();

    port_gpio_init();
}

hs_err_t cst816_read_register(uint8_t reg, uint8_t* pdata)
{
    return port_iic_read_register(reg, pdata);
}

hs_err_t cst816_write_register(uint8_t reg, uint8_t data)
{
    return port_iic_write_register(reg, data);
}

void cst816_reset(void)
{
    port_reset_pin_set_level(0);
    vTaskDelay(pdMS_TO_TICKS(10));
    port_reset_pin_set_level(1);
    vTaskDelay(pdMS_TO_TICKS(100));
}

hs_err_t cst816_get_touch_point(uint16_t* x, uint16_t* y)
{
    hs_err_t ret = 0;
    uint8_t buf[4] = {0};

    if (0 == port_iic_read_from_device(REG_XPOS_H, buf, 4)) {
        *x = ((buf[0] & 0x0F) << 8) | buf[1];
        *y = ((buf[2] & 0x0F) << 8) | buf[3];
    } else {
        /* read failed */
        ret = -1;
    }

    return ret;
}

uint8_t cst816_get_touch_point_num(void)
{
    uint8_t num = 0;

    if (HS_OK != cst816_read_register(REG_FINGER_NUM, &num)) {
        num = 0xFF; // read failed
    }

    return num;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

