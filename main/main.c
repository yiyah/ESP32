#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "iic.h"
#include "xl9555.h"

void app_main(void)
{
    uint8_t data = 0;
    LED_Init();
    ESP_LOGW("MAIN", "LED_Init");
    ESP_ERROR_CHECK(IIC_Master_Init());
    ESP_LOGW("MAIN", "IIC_Init");
    XL9555_Init();
    ESP_LOGW("MAIN", "XL9555_Init");
    XL9555_Config_GPIO(BEEP_PIN, XL9555_IO_DIR_OUTPUT);
    ESP_LOGW("MAIN", "CONFIG_GPIO");

    while(1)
    {
        LED_TOGGLE();
        XL9555_Write_pin(BEEP_PIN, data);
        data = !data;
        vTaskDelay(1000);
    }
}
