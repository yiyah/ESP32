/**
 * @file lcd.h
 *
 */

#ifndef PANEL_H
#define PANEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "font.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    PANEL_COLOR_RED     = 0x00F8,
    PANEL_COLOR_GREEN   = 0xE007,
    PANEL_COLOR_BLUE    = 0x1F00,
    PANEL_COLOR_WHITE   = 0xFFFF,
    PANEL_COLOR_BLACK   = 0x0000
} PANEL_RGB565_LITTE_ENDIAN;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void panel_init(void);
void panel_printf(const char* str, ...);
void panel_printf_ascii(uint16_t x, uint16_t y, uint8_t data, const ASCIIFont* afont);
void panel_set_color(uint16_t fore, uint16_t back);
void panel_set_cursor(uint16_t x, uint16_t y);
void panel_set_font(const Font* font);
void panel_set_ascii_font(const ASCIIFont* afont);
void panel_draw_image(const Image* img);
void panel_flush(void);
void panel_clear();

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PANEL_H */
