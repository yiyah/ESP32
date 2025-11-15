/**
 * @file panel.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "font.h"
#include "port_panel_driver.h"
#include "panel_conf.h"
#include "panel.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct panel
{
    uint8_t gram[PANEL_ROWS * PANEL_COLS * PANEL_BYTES_PER_PIXEL];
    const Font* font;

    struct
    {
        uint16_t fore;
        uint16_t back;
    } color;
    
    struct
    {
        uint16_t x;
        uint16_t y;
    } cursor;
} panel_t;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static panel_t s_panel;
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/
#define GET_GRAM_INDEX(x, y)        (((y)*PANEL_COLS + (x)) * PANEL_BYTES_PER_PIXEL)
#define GET_BYTES_PER_CHAR_ROW_ROW(w, h)    ((((w) + 7) / 8) * (h)) // 逐行式字模数据每个字符占用的字节数
#define GET_BYTES_PER_CHAR_COL_ROW(w, h)    ((((h) + 7) / 8) * (w)) // 列行式字模数据每个字符占用的字节数
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void panel_init(void)
{
    s_panel.font = &font16x16;
    s_panel.color.fore = PANEL_COLOR_WHITE;
    s_panel.color.back = PANEL_COLOR_BLACK;
    s_panel.cursor.x = 0;
    s_panel.cursor.y = 0;

    port_display_controller_init();
    panel_clear();
    panel_flush();
}

void panel_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buf[128]; // 根据需要调整大小或使用动态分配
    vsnprintf(buf, sizeof(buf), fmt, args); // 安全地格式化到 buf

    for (uint16_t i = 0; buf[i] != '\0'; i++) {
        panel_printf_ascii(s_panel.cursor.x, s_panel.cursor.y, (uint8_t)buf[i], s_panel.font->ascii);
        s_panel.cursor.x += s_panel.font->ascii->w;
        if (s_panel.cursor.x + s_panel.font->ascii->w > PANEL_HOR_RESOLUTION) {
            s_panel.cursor.x = 0;
            s_panel.cursor.y += s_panel.font->ascii->h;
        }
    }

    va_end(args);
}

/**
 * 列行式字模显示ASCII字符
 */
void panel_printf_ascii(uint16_t x, uint16_t y, uint8_t data, const ASCIIFont* afont)
{
    uint8_t char_index = data - ' ';
    uint16_t num_bytes_one_char = GET_BYTES_PER_CHAR_COL_ROW(afont->w, afont->h);  // 每个字符占用的字节数

    uint8_t* gram_start = &s_panel.gram[GET_GRAM_INDEX(x, y)];
    uint8_t* font_start = afont->chars + char_index * num_bytes_one_char;

    for (uint8_t row = 0; row < afont->h; row++) {
        uint8_t* gram_ptr = gram_start + row * PANEL_COLS * PANEL_BYTES_PER_PIXEL;
        uint8_t row_mask = 1 << (row % 8);  // 取决于字模数据的存储方式，这里假设是第一行的像素在最低位
        uint8_t* font_row_ptr = font_start + afont->w * (row / 8);

        for (uint8_t col = 0; col < afont->w; col++) {
            if (font_row_ptr[col] & row_mask) {
                gram_ptr[col * PANEL_BYTES_PER_PIXEL] = s_panel.color.fore & 0xFF;
                gram_ptr[col * PANEL_BYTES_PER_PIXEL + 1] = (s_panel.color.fore >> 8) & 0xFF;
            } 
        }
    }
}

void panel_set_color(uint16_t fore, uint16_t back)
{
    s_panel.color.fore = fore;
    s_panel.color.back = back;
}

void panel_set_cursor(uint16_t x, uint16_t y)
{
    s_panel.cursor.x = x;
    s_panel.cursor.y = y;
}

void panel_set_font(const Font* font)
{
    s_panel.font = font;
}

void panel_draw_image(const Image* img)
{

}

void panel_flush(void)
{
    port_draw_bitmap(0, 0, PANEL_HOR_RESOLUTION, PANEL_VER_RESOLUTION, s_panel.gram);
}

void panel_clear()
{
    for (uint32_t i = 0; i < sizeof(s_panel.gram)/2; i++) {
        s_panel.gram[i*2] = s_panel.color.back & 0xFF;
        s_panel.gram[i*2+1] = (s_panel.color.back >> 8) & 0xFF;
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/