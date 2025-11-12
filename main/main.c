#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "app_button.h"
#include "panel.h"

#define TAG "main"

void app_main(void)
{
    // button_init();
    panel_init();
    panel_set_color(PANEL_COLOR_WHITE, PANEL_COLOR_BLUE);
    panel_clear();
    panel_flush();
    while (1) {
        ESP_LOGE(TAG, "Main task running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
