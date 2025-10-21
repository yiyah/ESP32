/**
 * @file lcd.h
 *
 */

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

#define LCD_HOR_RESOLUTION      135     /* 水平 */
#define LCD_VER_RESOLUTION      240     /* 垂直 */

#define PIN_NUM_MISO            GPIO_NUM_NC
#define PIN_NUM_MOSI            GPIO_NUM_2
#define PIN_NUM_CLK             GPIO_NUM_1
#define PIN_NUM_CS              GPIO_NUM_0
#define PIN_NUM_DC              GPIO_NUM_3
#define PIN_NUM_RST             GPIO_NUM_4
#define PIN_NUM_BCKL            GPIO_NUM_5


#define PARALLEL_LINES          2
#define MAX_TRANSFER_SIZE       (PARALLEL_LINES * LCD_HOR_RESOLUTION * 2 + 8)

#define LCD_HOST                SPI2_HOST
#define LCD_SPI_CLOCK_HZ        40000000    /* 40 MHz */

#define LCD_BK_LIGHT_OFF_LEVEL  0
#define LCD_BK_LIGHT_ON_LEVEL   1

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lcd_init(void);
void lcd_clear(uint16_t color565);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LCD_H */
