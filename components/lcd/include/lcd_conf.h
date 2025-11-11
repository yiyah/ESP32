/**
 * @file lcd_conf.h
 *
 */

#ifndef LCD_CONF_H
#define LCD_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/* LCD Model Selection (from Kconfig) */
#ifdef CONFIG_LCD_MODEL_169
    #define LCD_HOR_RESOLUTION      240     /* 水平 */
    #define LCD_VER_RESOLUTION      280     /* 垂直 */
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

#elif CONFIG_LCD_MODEL_114
    #define LCD_HOR_RESOLUTION      135     /* 水平 */
    #define LCD_VER_RESOLUTION      240     /* 垂直 */
    #define LCD_GAP_X               52
    #define LCD_GAP_Y               40
    #define LCD_INVERT_COLOR        true    /* invert color for ST7789 */

    /* PIN define */
    #define PIN_NUM_MISO            GPIO_NUM_NC
    #define PIN_NUM_MOSI            GPIO_NUM_2
    #define PIN_NUM_CLK             GPIO_NUM_1
    #define PIN_NUM_CS              GPIO_NUM_0
    #define PIN_NUM_DC              GPIO_NUM_3
    #define PIN_NUM_RST             GPIO_NUM_4
    #define PIN_NUM_BCKL            GPIO_NUM_5

#else
    #error "No LCD model selected. Please set one in menuconfig."
#endif

#define LCD_ROWS                LCD_VER_RESOLUTION
#define LCD_COLS                LCD_HOR_RESOLUTION

#define PARALLEL_LINES          2
#define MAX_TRANSFER_SIZE       (PARALLEL_LINES * LCD_HOR_RESOLUTION * 2 + 8)

#define LCD_HOST                SPI2_HOST
#define LCD_SPI_CLOCK_HZ        20000000    /* 40 MHz */

#define LCD_BK_LIGHT_OFF_LEVEL  1
#define LCD_BK_LIGHT_ON_LEVEL   (!LCD_BK_LIGHT_OFF_LEVEL)

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

#endif /* LCD_CONF_H */
