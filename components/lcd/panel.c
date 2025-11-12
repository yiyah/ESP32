/**
 * @file panel.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
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
    uint16_t gram[PANEL_ROWS * PANEL_COLS];
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

void panel_printf(const char* str, ...)
{

}

void panel_printf_ascii(const uint8_t data)
{

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
        s_panel.gram[i] = s_panel.color.back;
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/