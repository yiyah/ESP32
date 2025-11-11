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
#include "lcd_conf.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    LCD_COLOR_RED     = 0x00F8,
    LCD_COLOR_GREEN   = 0xE007,
    LCD_COLOR_BLUE    = 0x1F00,
    LCD_COLOR_WHITE   = 0xFFFF,
    LCD_COLOR_BLACK   = 0x0000
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
