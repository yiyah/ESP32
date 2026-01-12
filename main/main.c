#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "sht3x.h"
void app_main(void)
{

    sht3x_main();
    while(1)
    {
        printf("Hello-ESP32\r\n");
        vTaskDelay(1000);
    }
}