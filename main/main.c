#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "sht3x.h"
#include "ina226.h"
#include "bsp.h"
#include "app_task.h"
#include "sensors_data_typs.h"


void app_main(void)
{
    bsp_init();

    sht3x_main();

    app_task_init();
    
    // 获取INA226队列
    QueueHandle_t ina226_queue = app_task_get_ina226_queue();
    ina226_data_t ina226_data;
    
    while(1)
    {
        // 尝试从队列读取数据
        if (ina226_queue != NULL) {
            if (xQueueReceive(ina226_queue, &ina226_data, pdMS_TO_TICKS(100)) == pdTRUE) {
                ESP_LOGI("MAIN", "INA226 - Voltage: %.2f mV, Current: %.2f mA, Power: %.2f mW", 
                        ina226_data.voltage, ina226_data.current, ina226_data.power);
            }
        }
        
        printf("Hello-ESP32\r\n");
    }
}
