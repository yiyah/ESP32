/**
 * @file test_driver.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "../include/panel.h"
/*********************
 *      DEFINES
 *********************/
#define LOG_TAG "[driver]"
#define LOG(fmt, ...)   printf(LOG_TAG ": " fmt, ##__VA_ARGS__)

/**********************
 *      TYPEDEFS
 **********************/
typedef struct test_driver
{
    panel_t panel;      /*!< 继承 */
    int     dummy;
} test_driver_t;


/**********************
 *  STATIC PROTOTYPES
 **********************/
static panel_status_t _init(const panel_handle_t handle);
static panel_status_t _deinit(const panel_handle_t handle);
static panel_status_t _draw_bitmap(const panel_handle_t handle, int x, int y, int w, int h, const uint8_t *data);
static panel_status_t _set_backlight(const panel_handle_t handle, bool on);

/**********************
 *  STATIC VARIABLES
 **********************/
static panel_ops_t test_driver_ops = {
    .init = _init,
    .deinit = _deinit,
    .draw_bitmap = _draw_bitmap,
    .set_backlight = _set_backlight,
};

static test_driver_t test_driver_instance1;
static test_driver_t test_driver_instance2;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
panel_status_t driver_test_init(void)
{
    panel_status_t ret = PANEL_OK;
    LOG("Registering test panel driver 1...\n");
    ret = panel_driver_register("test_panel_driver1", &test_driver_instance1.panel, &test_driver_ops);
    if (ret != PANEL_OK) {
        LOG("Failed to register test panel driver with error code: %d\n", ret);
    } else {
        LOG("Test panel driver registered successfully.\n");
    }

    LOG("Registering test panel driver 2...\n");
    ret = panel_driver_register("test_panel_driver2", &test_driver_instance2.panel, &test_driver_ops);
    if (ret != PANEL_OK) {
        LOG("Failed to register test panel driver with error code: %d\n", ret);
    } else {
        LOG("Test panel driver registered successfully.\n");
    }
    return ret;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

static panel_status_t _init(const panel_handle_t handle)
{
    // Mock initialization logic
    return PANEL_OK;
}
static panel_status_t _deinit(const panel_handle_t handle)
{
    // Mock deinitialization logic
    return PANEL_OK;
}
static panel_status_t _draw_bitmap(const panel_handle_t handle, int x, int y, int w, int h, const uint8_t *data)
{
    // Mock drawing logic
    return PANEL_OK;
}
static panel_status_t _set_backlight(const panel_handle_t handle, bool on)
{
    // Mock backlight control logic
    return PANEL_OK;
}