#ifndef __LCD_H
#define __LCD_H


typedef enum
{
    LCD_DISP_LANDSCAPE = 0,     /* 横屏 */
    LCD_DISP_PORTRAIT,          /* 竖屏 */
} LCD_DISP_DIRECTION;


void vLCD_Init(void);
void vLCD_Clear(uint16_t u16Color);
void vLCD_SetDisplayDirection(LCD_DISP_DIRECTION dirction);


#endif /* __LCD_H */
