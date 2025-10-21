#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "app_button.h"
#include "lcd.h"

#define TAG "main"

void app_main(void)
{
    button_init();
    lcd_init();
    while (1) {
        ESP_LOGE(TAG, "Main task running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
