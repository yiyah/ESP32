/**
 * @file test_bsp.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "../include/panel.h"
#include "../driver/driver_st7789v_esp32.h"

extern panel_status_t driver_test_init(void);

/*********************
 *      DEFINES
 *********************/
#define LOG_TAG "[BSP]"
#define LOG(fmt, ...)   printf(LOG_TAG ": " fmt, ##__VA_ARGS__)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void bsp_init(void)
{
    // Initialize board support package (BSP) - mock implementation
    LOG("BSP initialized (mock)\n");
    panel_status_t ret = driver_test_init();
    if (ret != PANEL_OK) {
        LOG("driver_test_init failed with error code: %d\n", ret);
    }
    LOG("BSP finished initialization\n");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

