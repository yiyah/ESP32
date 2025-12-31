/*
 * test_panel.c - simple test harness using mock port
 * Build as a host executable to run unit tests quickly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/panel.h"

extern void bsp_init(void);

#define LOG_TAG "[main]"
#define LOGG_TAG "[app]"
#define LOG(fmt, ...)   printf(LOG_TAG ": " fmt, ##__VA_ARGS__)
#define LOGG(fmt, ...)  printf(LOGG_TAG ": " fmt, ##__VA_ARGS__)

void app(void)
{   
    panel_status_t ret = PANEL_OK;
    panel_handle_t handle1 = NULL;
    panel_handle_t handle2 = NULL;
    panel_config_t cfg = {
        .width = 240,
        .height = 320,
        .bpp = 16,
        .rotation = 0,
        .user_data = NULL
    };
    ret = panel_init("test_panel_driver1", &cfg, &handle1);
    if (ret != PANEL_OK) {
        LOGG("panel_init failed with error code: %d\n", ret);
    } else {
        LOGG("panel_init succeeded\n");
    }

    ret = panel_init("test_panel_driver2", &cfg, &handle2);
    if (ret != PANEL_OK) {
        LOGG("panel_init failed with error code: %d\n", ret);
    } else {
        LOGG("panel_init succeeded\n");
        
    }
}

int main(void)
{
    LOG("panel test start\n");

    bsp_init();
    app();
  
    LOG("panel test done\n");
    return 0;
}
