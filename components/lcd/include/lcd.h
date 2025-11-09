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

#define LCD_HOR_RESOLUTION      240     /* 水平 */
#define LCD_VER_RESOLUTION      280     /* 垂直 */
#define LCD_ROWS                LCD_VER_RESOLUTION
#define LCD_COLS                LCD_HOR_RESOLUTION

#define PIN_NUM_MISO            GPIO_NUM_NC
#define PIN_NUM_MOSI            GPIO_NUM_11
#define PIN_NUM_CLK             GPIO_NUM_12
#define PIN_NUM_CS              GPIO_NUM_10
#define PIN_NUM_DC              GPIO_NUM_39
#define PIN_NUM_RST             GPIO_NUM_17
#define PIN_NUM_BCKL            GPIO_NUM_38


#define PARALLEL_LINES          2
#define MAX_TRANSFER_SIZE       (PARALLEL_LINES * LCD_HOR_RESOLUTION * 2 + 8)

#define LCD_HOST                SPI2_HOST
#define LCD_SPI_CLOCK_HZ        20000000    /* 40 MHz */

#define LCD_BK_LIGHT_OFF_LEVEL  1
#define LCD_BK_LIGHT_ON_LEVEL   (!LCD_BK_LIGHT_OFF_LEVEL)

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    LCD_RED     = 0x00F8,
    LCD_GREEN   = 0xE007,
    LCD_BLUE    = 0x1F00,
    LCD_WHITE   = 0xFFFF,
    LCD_BLACK   = 0x0000
} LCD_COLOR565_LITTE_ENDIAN;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lcd_init(void);
void lcd_clear(uint16_t color565);
void lcd_set_pixel(uint16_t x, uint16_t y, uint16_t color565);
void lcd_flush(void);
void lcd_printf_ascii(uint8_t ascii);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LCD_H */
