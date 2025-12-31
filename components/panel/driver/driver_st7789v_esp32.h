/**
 * @file driver_st7789v_esp32.h
 *
 */

#ifndef DRIVER_ST7789V_ESP32_H
#define DRIVER_ST7789V_ESP32_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "panel.h"

/*********************
 *      DEFINES
 *********************/
#define LCD_GAP_X               0
#define LCD_GAP_Y               20
#define LCD_INVERT_COLOR        true    /* invert color for ST7789 */

/* PIN define */
#define PIN_NUM_MISO            GPIO_NUM_NC
#define PIN_NUM_MOSI            GPIO_NUM_11
#define PIN_NUM_CLK             GPIO_NUM_12
#define PIN_NUM_CS              GPIO_NUM_10
#define PIN_NUM_DC              GPIO_NUM_39
#define PIN_NUM_RST             GPIO_NUM_17
#define PIN_NUM_BCKL            GPIO_NUM_38

#define PARALLEL_LINES              2
#define MAX_TRANSFER_SIZE(row)           (PARALLEL_LINES * (row) * 2 + 8)

#define LCD_HOST                    SPI2_HOST
#define LCD_SPI_CLOCK_HZ            40000000    /* 40 MHz */

#define LCD_BK_LIGHT_OFF_LEVEL      1
#define LCD_BK_LIGHT_ON_LEVEL       (!LCD_BK_LIGHT_OFF_LEVEL)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* call in bsp_init() */
panel_status_t driver_st7789v_init(void);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRIVER_ST7789V_ESP32_H */
