/**
 * @file lcd.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "panel.h"
/*********************
 *      DEFINES
 *********************/

#define LCD_VER_RESOLUTION      240     /* w */
#define LCD_HOR_RESOLUTION      280     /* h */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static panel_handle_t s_panel_handle = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lcd_init(void)
{
    panel_config_t cfg = {
        .width = LCD_VER_RESOLUTION,
        .height = LCD_HOR_RESOLUTION,
        .bpp = 16,
        .rotation = 0,
        .user_data = NULL
    };
    panel_init("st7789v", &cfg, &s_panel_handle);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

