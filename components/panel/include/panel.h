/**
 * @file panel.h
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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    PANEL_OK = 0,
    PANEL_ERR_INVALID_ARG,
    PANEL_ERR_NO_RESOURCE,
    PANEL_ERR_IO,
    PANEL_ERR_TIMEOUT,
    PANEL_ERR_UNSUPPORTED,
    PANEL_ERR_BUSY,
    PANEL_ERR_UNKNOWN
} panel_status_t;

/* app provice */
typedef struct
{
    uint16_t width;
    uint16_t height;
    uint8_t bpp; /* bits per pixel */
    uint32_t rotation;
    void *user_data; /* user provided framebuffer, can be NULL */
} panel_config_t;

typedef struct panel* panel_handle_t;

/* driver provide */
typedef struct
{
    panel_status_t (*init)(const panel_handle_t handle);
    panel_status_t (*deinit)(const panel_handle_t handle);
    panel_status_t (*draw_bitmap)(const panel_handle_t handle, int x, int y, int w, int h, const uint8_t *data);
    panel_status_t (*set_backlight)(const panel_handle_t handle, bool on);
} panel_ops_t;

/* driver provide */
typedef struct panel {
    struct panel* next;

    const char* driver_name;
    const panel_config_t cfg;
    const panel_ops_t *ops;
    uint8_t *framebuf; /* framebuffer */
} panel_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* for APP */
panel_status_t panel_init(const char* driver_name, panel_handle_t *handle_out, panel_config_t* config);
panel_status_t panel_draw(panel_handle_t handle, int x, int y, int w, int h, const uint8_t* data);
panel_status_t panel_clear(panel_handle_t handle);
panel_status_t panel_flush(panel_handle_t handle);
panel_status_t panel_set_backlight(panel_handle_t handle, bool on);

/* for driver */
panel_status_t panel_driver_register(const char* driver_name,
                                     const panel_handle_t handle,
                                     const panel_ops_t* ops);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_TEMPL_H */
