/**
 * @file task.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "sensors_data_typs.h"
#include "ina226.h"
/*********************
 *      DEFINES
 *********************/
#define TAG "app_task"
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static QueueHandle_t ina226_queue = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void app_task_init(void)
{
    // 创建队列
    ina226_queue = xQueueCreate(1, sizeof(ina226_data_t));
    if (ina226_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }

    // 创建INA226任务
    BaseType_t ret = xTaskCreate(ina226_main,
                "ina226 task",
                2*1024,
                (void *)ina226_queue,
                3,
                NULL);
    
    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to create ina226 task");
        vQueueDelete(ina226_queue);
        ina226_queue = NULL;
    }
}

QueueHandle_t app_task_get_ina226_queue(void)
{
    return ina226_queue;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
