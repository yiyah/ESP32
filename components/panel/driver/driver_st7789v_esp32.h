/**
 * @file driver_st7789v_esp32.h
 *
 */

#ifndef DRIVER_ST7789V_ESP32_H
#define DRIVER_ST7789V_ESP32_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "panel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* call in bsp_init() */
panel_status_t driver_st7789v_init(void);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRIVER_ST7789V_ESP32_H */
