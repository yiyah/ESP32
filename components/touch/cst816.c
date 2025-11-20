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
static hs_err_t cst816_read_register(uint8_t reg, uint8_t* pdata);
static hs_err_t cst816_write_register(uint8_t reg, uint8_t data);

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

void cst816_reset(void)
{
    port_reset_pin_set_level(0);
    vTaskDelay(pdMS_TO_TICKS(10));
    port_reset_pin_set_level(1);
    vTaskDelay(pdMS_TO_TICKS(100));
}

hs_err_t cst816_get_touch_point(uint16_t* x, uint16_t* y)
{
    hs_err_t ret = HS_OK;
    uint8_t buf[4] = {0};

    if (0 == port_iic_read_from_device(REG_XPOS_H, buf, 4)) {
        *x = ((buf[0] & 0x0F) << 8) | buf[1];
        *y = ((buf[2] & 0x0F) << 8) | buf[3];
    } else {
        ret = HS_FAIL;
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

uint8_t cst816_get_chip_id(void)
{
    uint8_t chip_id = 0xFF;

    if (HS_OK != cst816_read_register(REG_CHIP_ID, &chip_id)) {
        chip_id = 0x0; // read failed
        printf("CST816 read chip id failed!\n");
    }

    return chip_id;
}

hs_err_t cst816_enable_motion(cst816_motion_t motion)
{
    return cst816_write_register(REG_MOTION_MASK, (uint8_t)motion);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static hs_err_t cst816_read_register(uint8_t reg, uint8_t* pdata)
{
    return port_iic_read_register(reg, pdata);
}

static hs_err_t cst816_write_register(uint8_t reg, uint8_t data)
{
    return port_iic_write_register(reg, data);
}