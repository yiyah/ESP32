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

#include "sensors_data_typs.h"
#include "ina226.h"
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
void ina226_main(void *pvParameters)
{
    ina226_data_t ina226;
    QueueHandle_t data_queue = (QueueHandle_t)pvParameters;

    ina226_basic_init(INA226_ADDRESS_0, 0.05);

    for(;;)
    {
        ina226_basic_read(&ina226.voltage, &ina226.current, &ina226.power);
        // ESP_LOGI(TAG, "mV: %.2f mV, mA: %.2f mA, mW: %.2f mW.", ina226.voltage, ina226.current, ina226.power);
        xQueueOverwrite(data_queue, &ina226);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

