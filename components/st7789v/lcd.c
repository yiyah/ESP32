#include "../xl9555/xl9555.h"
#include "st7789v.h"
#include "lcd.h"


#define ST7789V_PIN_PWR  GPIO_NUM_40

#define LCD_PIXELS_SIZE     (320U * 240U)
#define LCD_BUFF_SIZE       (LCD_PIXELS_SIZE * 2U)

uint8_t g_LCD_BUFF[LCD_BUFF_SIZE] = {0};

void vLCD_SetDisplayDirection(LCD_DISP_DIRECTION dirction)
{
    if (LCD_DISP_LANDSCAPE == dirction)
    {
        /**
         * width(x): 320
         * height(y): 240
         */
        u8ST7789V_Write_CMD(CMD_MADCTL);
        u8ST7789V_Write_DATA((uint8_t[]){0x00}, 1);
    }
    else
    {
        /**
         * width(x): 240
         * height(y): 320
         */
        u8ST7789V_Write_CMD(CMD_MADCTL);
        u8ST7789V_Write_DATA((uint8_t[]){0x60}, 1);
    }
}

void vLCD_SetWindow(uint16_t u16X_star, uint16_t u16Y_star,
                    uint16_t u16X_end, uint16_t u16Y_end)
{
    u8ST7789V_Write_CMD(CMD_CASET);
    u8ST7789V_Write_DATA((uint8_t[]){
        (u16X_star >> 8) & 0xFF,        /* high byte */
        u16X_star & 0xFF,               /* low byte */
        (u16X_end >> 8) & 0xFF,
        u16X_end & 0xFF
    }, 4);

    u8ST7789V_Write_CMD(CMD_RASET);
    u8ST7789V_Write_DATA((uint8_t[]){
        (u16Y_star >> 8) & 0xFF,        /* high byte */
        u16Y_star & 0xFF,               /* low byte */
        (u16Y_end >> 8) & 0xFF,
        u16Y_end & 0xFF
    }, 4);

    u8ST7789V_Write_CMD(CMD_RAMWR);
}

void vLCD_Clear(uint16_t u16Color)
{
    uint8_t u8arrColor[2] = {(u16Color >> 8) & 0xFF, u16Color & 0xFF};

    vLCD_SetWindow(0, 0, 100-1, 200-1);

    for (uint32_t i = 0; i < LCD_PIXELS_SIZE - 1; i++)
    {
        u8ST7789V_Write_DATA(u8arrColor, 2);
    }
}

void vLCD_Power(uint8_t u8State)
{
    XL9555_Write_pin(LCD_PWR_PIN, u8State);
}

void vLCD_Init(void)
{
    ST7789V_Init();
    vLCD_Power(1);
}
