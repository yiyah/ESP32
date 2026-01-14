#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "sht3x.h"
#include "ina226.h"
#include "bsp.h"


void app_main(void)
{
    bsp_init();

    sht3x_main();
    ina226_main();
    
    while(1)
    {
        printf("Hello-ESP32\r\n");
        vTaskDelay(1000);
    }
}
