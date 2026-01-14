/**
 * @file ina226_main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "esp_log.h"
#include "driver_ina226_basic.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*********************
 *      DEFINES
 *********************/
#define TAG "ina226"
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
void ina226_main(void)
{
    ina226_basic_init(INA226_ADDRESS_0, 0.05);
    float mV, mA, mW;
    while (1)
    {
        ina226_basic_read(&mV, &mA, &mW);
        ESP_LOGI(TAG, "ina226: mV: %.2f mV, mA: %.2f mA, mW: %.2f mW.", mV, mA, mW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

