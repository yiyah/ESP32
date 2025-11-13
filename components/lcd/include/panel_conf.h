/**
 * @file panel_conf.h
 *
 */

#ifndef PANEL_CONF_H
#define PANEL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
/* Ensure generated configuration macros (CONFIG_*) are available */
#include "sdkconfig.h"

/*********************
 *      DEFINES
 *********************/
#if defined(CONFIG_PANEL_MODEL_169)
    #define PANEL_HOR_RESOLUTION    240     /* 水平有多少像素，即 w */
    #define PANEL_VER_RESOLUTION    280     /* 垂直有多少像素，即 h */
    #define PANEL_BITS_PER_PIXEL    16      /* RGB显示屏 */
#elif defined(CONFIG_PANEL_MODEL_114)
    #define PANEL_HOR_RESOLUTION    135     /* 水平有多少像素，即 w */
    #define PANEL_VER_RESOLUTION    240     /* 垂直有多少像素，即 h */
    #define PANEL_BITS_PER_PIXEL    16      /* RGB显示屏 */
#else
    #error "No PANEL model selected. Please set one in menuconfig."
#endif

#define PANEL_ROWS                  PANEL_VER_RESOLUTION
#define PANEL_COLS                  PANEL_HOR_RESOLUTION
#define PANEL_BYTES_PER_PIXEL       (((PANEL_BITS_PER_PIXEL) + 7) / 8)
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*PANEL_CONF_H*/