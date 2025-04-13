#ifndef __LCD_H
#define __LCD_H

#include "lcd_font.h"

typedef enum
{
    LCD_DISP_LANDSCAPE = 0,     /* 横屏 */
    LCD_DISP_PORTRAIT,          /* 竖屏 */
} LCD_DISP_DIRECTION;

/* 常用颜色值 */
#define LCD_COLOR_WHITE           0xFFFF      /* 白色 */
#define LCD_COLOR_BLACK           0x0000      /* 黑色 */
#define LCD_COLOR_RED             0xF800      /* 红色 */
#define LCD_COLOR_GREEN           0x07E0      /* 绿色 */
#define LCD_COLOR_BLUE            0x001F      /* 蓝色 */ 
#define LCD_COLOR_MAGENTA         0XF81F      /* 品红色/紫红色 = BLUE + RED */
#define LCD_COLOR_YELLOW          0XFFE0      /* 黄色 = GREEN + RED */
#define LCD_COLOR_CYAN            0X07FF      /* 青色 = GREEN + BLUE */  


void vLCD_Init(void);
void vLCD_Clear(uint16_t u16Color);
void vLCD_SetDisplayDirection(LCD_DISP_DIRECTION dirction);
void LCD_vShow_ASCII_Char(const uint16_t u16X, const uint16_t u16Y,
                          const uint8_t u8Char, const ASCIIFont *pfont, const uint16_t u16Color);
void LCD_vShow_Char(const uint16_t u16X, const uint16_t u16Y,
                    const uint8_t u8Char, const Font *pfont, const uint16_t u16Color);


#endif /* __LCD_H */
