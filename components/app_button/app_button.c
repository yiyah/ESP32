/**
 * @file app_button.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "esp_log.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "app_button.h"

/*********************
 *      DEFINES
 *********************/
#define BUTTON_IO_NUM           5
#define BUTTON_ACTIVE_LEVEL     0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void button_event_cb(void *arg, void *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static const char *TAG = "button";

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void button_init(void)
{
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = BUTTON_IO_NUM,
        .active_level = BUTTON_ACTIVE_LEVEL,
    };

    button_handle_t btn = NULL;
    esp_err_t ret = iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &btn);

    // iot_button_register_cb(btn, BUTTON_PRESS_DOWN, NULL, button_event_cb, NULL);
    // iot_button_register_cb(btn, BUTTON_PRESS_UP, NULL, button_event_cb, NULL);
    iot_button_register_cb(btn, BUTTON_PRESS_REPEAT, NULL, button_event_cb, NULL);
    // iot_button_register_cb(btn, BUTTON_PRESS_REPEAT_DONE, NULL, button_event_cb, NULL);
    iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, button_event_cb, NULL);
    iot_button_register_cb(btn, BUTTON_DOUBLE_CLICK, NULL, button_event_cb, NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void button_event_cb(void *arg, void *data)
{
    button_event_t event = iot_button_get_event(arg);
    ESP_LOGI(TAG, "%s", iot_button_get_event_str(event));
    if (BUTTON_PRESS_REPEAT == event || BUTTON_PRESS_REPEAT_DONE == event) {
        ESP_LOGI(TAG, "\tREPEAT[%d]", iot_button_get_repeat(arg));
    }

    if (BUTTON_PRESS_UP == event || BUTTON_LONG_PRESS_HOLD == event || BUTTON_LONG_PRESS_UP == event) {
        ESP_LOGI(TAG, "\tTICKS[%"PRIu32"]", iot_button_get_ticks_time(arg));
    }

    if (BUTTON_MULTIPLE_CLICK == event) {
        ESP_LOGI(TAG, "\tMULTIPLE[%d]", (int)data);
    }
}