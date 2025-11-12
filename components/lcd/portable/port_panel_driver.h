/**
 * @file port_panel_driver.h
 *
 */

#ifndef PORT_PANEL_DRIVER_H
#define PORT_PANEL_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void port_display_controller_init(void);
void port_draw_bitmap(uint16_t x, uint16_t y, uint16_t x_end, uint16_t y_end, const void* data);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*PORT_PANEL_DRIVER_H*/