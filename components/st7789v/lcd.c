#include "../xl9555/xl9555.h"
#include "st7789v.h"
#include "lcd.h"

#define ST7789V_PIN_PWR  GPIO_NUM_40

#define LCD_LANDSCAPE_PIXEL_WIDTH   (320U)
#define LCD_LANDSCAPE_PIXEL_HEIGHT  (240U)
#define LCD_PIXELS_SIZE             (LCD_LANDSCAPE_PIXEL_WIDTH * LCD_LANDSCAPE_PIXEL_HEIGHT)
#define LCD_BUFF_SIZE               (LCD_PIXELS_SIZE * 2U)

#define GET_FONT_CHAR_SIZE_BYTE(w, h)       ((w) * ((((h)+7)/8)))

uint8_t g_LCD_BUFF[LCD_BUFF_SIZE] = {0};

void vLCD_SetWindow(uint16_t u16X_star, uint16_t u16Y_star,
    uint16_t u16X_end, uint16_t u16Y_end);

/* 逐行式 */
void LCD_vShow_ASCII_Char(const uint16_t u16X, const uint16_t u16Y,
                          const uint8_t u8Char, const ASCIIFont *pfont, const uint16_t u16Color)
{
    uint8_t offset = 0;
    uint16_t u8CharSize_byte = GET_FONT_CHAR_SIZE_BYTE(pfont->w, pfont->h);
    const uint8_t *pHead = pfont->chars + ((u8Char - ' ') * (u8CharSize_byte + offset)) + offset;
    uint16_t u16SetColor = u16Color;

    // vLCD_SetWindow(u16X, u16Y, u16X + 8 * ((pfont->w + 7) / 8) - 1, u16Y + pfont->h - 1);
    vLCD_SetWindow(u16X, u16Y, u16X + pfont->w - 1, u16Y + pfont->h - 1);

    for (uint16_t i = 0; i < u8CharSize_byte; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (*pHead & (1 << (7-j)))      /* 取模走向：顺向。就用 "7-j" */
            {
                u16SetColor = u16Color;
            }
            else
            {
                u16SetColor = 0x0000;
            }
            u8ST7789V_Write_DATA((uint8_t[]){(u16SetColor >> 8) & 0xFF, u16SetColor & 0xFF}, 2);
        }
        pHead++;
    }
}

/* 逐列式 */
void LCD_vShow_Char(const uint16_t u16X, const uint16_t u16Y,
                    const uint8_t u8Char, const Font *pfont, const uint16_t u16Color)
{
    uint8_t offset = 4;     /* 字模数据前4个字节是UTF-8 */
    uint16_t u8CharSize_byte = GET_FONT_CHAR_SIZE_BYTE(pfont->w, pfont->h);
    const uint8_t *pHead = pfont->chars + ((u8Char - ' ') * (u8CharSize_byte + offset)) + offset;
    uint16_t u16SetColor = u16Color;
    int oneCol_size_byte = (pfont->h + 7) / 8;  // 每列字模数据的字节数

    vLCD_SetWindow(u16X, u16Y, u16X + pfont->w - 1, u16Y + pfont->h - 1);

    for (uint16_t i = 0; i < pfont->h; i++)
    {
        if ((i % 8 == 0)
        && (i != 0))
        {
            pHead ++;
        }

        for (uint16_t j = 0; j < pfont->w; j++)
        {
            if (*(pHead + j * oneCol_size_byte) & (1 << (i % 8)))
            {
                u16SetColor = u16Color;
            }
            else
            {
                u16SetColor = 0x0000;
            }
            u8ST7789V_Write_DATA((uint8_t[]){(u16SetColor >> 8) & 0xFF, u16SetColor & 0xFF}, 2);
        }
    }
}

/* 逐行式 */
// void LCD_vShow_Char(uint16_t u16X, uint16_t u16Y, uint8_t u8Char, Font *pfont, uint16_t u16Color)
// {
//     uint8_t offset = 4;
//     uint16_t u8CharSize_byte = GET_FONT_CHAR_SIZE_BYTE(pfont->w, pfont->h);
//     const uint8_t *pHead = pfont->chars + ((u8Char - ' ') * (u8CharSize_byte + offset)) + offset;
//     uint16_t u16SetColor = u16Color;

//     vLCD_SetWindow(u16X, u16Y, u16X + 8 * ((pfont->w + 7) / 8) - 1, u16Y + pfont->h - 1);

//     for (uint16_t i = 0; i < u8CharSize_byte; i++)
//     {
//         for (uint8_t j = 0; j < 8; j++)
//         {
//             if (*pHead & (1 << (j)))            /* 取模走向：逆向 */
//             // if (*pHead & (1 << (7-j)))       /* 取模走向：顺向 */
//             {
//                 u16SetColor = u16Color;
//             }
//             else
//             {
//                 u16SetColor = 0x0000;
//             }
//             u8ST7789V_Write_DATA((uint8_t[]){(u16SetColor >> 8) & 0xFF, u16SetColor & 0xFF}, 2);
//         }
//         pHead++;
//     }
// }

void vLCD_SetDisplayDirection(LCD_DISP_DIRECTION dirction)
{
    if (LCD_DISP_LANDSCAPE == dirction)
    {
        /**
         * width(x): 320
         * height(y): 240
         */
        u8ST7789V_SetScanDirection(ST7789V_SCAN_RLUD, 1);
    }
    else
    {
        /**
         * width(x): 240
         * height(y): 320
         */
        u8ST7789V_SetScanDirection(ST7789V_SCAN_LRUD, 0);
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
    vLCD_SetDisplayDirection(LCD_DISP_LANDSCAPE);
    vLCD_SetWindow(0, 0, LCD_LANDSCAPE_PIXEL_WIDTH - 1, LCD_LANDSCAPE_PIXEL_HEIGHT - 1);
    
    for (uint32_t i = 0; i < LCD_PIXELS_SIZE / 2; i++)
    {
        g_LCD_BUFF[i*2]   = (u16Color >> 8) & 0xFF;
        g_LCD_BUFF[i*2+1] = u16Color & 0xFF;
    }

    for (uint16_t i = 0; i < 240; i++)
    {
        u8ST7789V_Write_DATA(g_LCD_BUFF, 320*2);
    }
}

void vLCD_Power(uint8_t u8State)
{
    XL9555_Write_pin(LCD_PWR_PIN, u8State);
}

void vLCD_Init(void)
{
    ST7789V_Init();
    vLCD_SetDisplayDirection(LCD_DISP_LANDSCAPE);
    vLCD_Power(1);
    vLCD_Clear(0xFFFF);
}
