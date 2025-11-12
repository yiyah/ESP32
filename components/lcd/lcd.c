/**
 * @file lcd.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/spi_master.h"
#include "lcd.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct lcd
{
    

} lcd_t;
 /**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lcd_t lcd;
static esp_lcd_panel_io_handle_t io_handle;

/**********************
 *      MACROS
 **********************/
#define GET_GRAM_INDEX(x, y)        ((y)*LCD_COLS + (x))
#define GET_BYTES_PER_CHAR(w, h)    ((((w) + 7) / 8) * (h))
/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lcd_printf(const char* str)
{

}

/**
 * 逐行式字模显示ASCII字符
 */
void lcd_printf_ascii(uint8_t ascii)
{
    uint8_t char_index = ascii - ' ';
    uint32_t gram_index = GET_GRAM_INDEX(lcd.point.x, lcd.point.y);

    // ASCIIFont* afont = lcd.font->ascii;
    printf("char_index: %d\n", char_index);

    const Font* afont = lcd.font;
    
    uint16_t num_bytes_in_row = (afont->w + 7) / 8; // 字符 每行 占用的字节数
    uint16_t num_bytes_one_char = GET_BYTES_PER_CHAR(afont->w, afont->h) + 4;  // 每个字符占用的字节数, 前4字节为utf8编码
    
    const uint8_t* char_map = &afont->chars[char_index * num_bytes_one_char + 4]; // +4 跳过前4字节的utf8编码

    for (uint8_t row = 0; row < afont->h; row++) {
        for (uint8_t col = 0; col < afont->w; col++) {

            if (char_map[col / 8] & (0x1 << (col % 8))) {
                lcd.gram[gram_index + col] = lcd.color.fore;
            }/* else {
                lcd.gram[gram_index + col] = lcd.color.back;
                printf(" ");
            }*/
        }
        char_map += num_bytes_in_row;
        gram_index += LCD_COLS;
    }
    lcd.point.x += afont->w;
}

/**
 * x: 0 ~ LCD_HOR_RESOLUTION-1
 * y: 0 ~ LCD_VER_RESOLUTION-1
 */
void lcd_set_pixel(uint16_t x, uint16_t y, uint16_t color565)
{
    uint32_t index = GET_GRAM_INDEX(x, y);
    lcd.gram[index] = color565;
}

void lcd_flush(void)
{
    esp_lcd_panel_draw_bitmap(lcd.panel_handle, 0, 0 , LCD_HOR_RESOLUTION, LCD_VER_RESOLUTION, lcd.gram);
}

void lcd_clear(uint16_t color565)
{
    for (uint32_t i = 0; i < sizeof(lcd.gram)/2; i++) {
        lcd.gram[i] = color565;
    }
    // esp_lcd_panel_draw_bitmap(lcd.panel_handle, 0, 0 , LCD_HOR_RESOLUTION - 1, LCD_VER_RESOLUTION - 1, lcd.gram);
}

void lcd_init(void)
{

    lcd_clear(LCD_COLOR_GREEN);
    lcd_flush();

    lcd.font = &font12x12;
    lcd.color.fore = LCD_COLOR_WHITE;
    lcd.color.back = LCD_COLOR_BLACK;
    lcd.point.x = 0;
    lcd.point.y = 0;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
