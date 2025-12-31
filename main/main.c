#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "app_button.h"
#include "lcd.h"
#define TAG "main"

extern void bsp_init(void);


void app_main(void)
{
    bsp_init();

    lcd_init();

    while (1) {
        ESP_LOGI(TAG, "Main task running...");
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
