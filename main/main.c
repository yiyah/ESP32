#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "app_button.h"
#include "panel.h"
#include "cst816.h"
#include "driver/gpio.h"
#define TAG "main"

void app_main(void)
{
    // button_init();
    // CST816_Init();
    panel_init();
    panel_set_color(PANEL_COLOR_WHITE, PANEL_COLOR_BLUE);
    panel_clear();
    panel_set_cursor(10, 10);
    panel_printf("Hello, HPanel!123456778901234567890");
    panel_flush();
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_2),
        .mode = GPIO_MODE_INPUT,
    };
    gpio_config(&io_conf);
    uint8_t a, a_pre = 0;
    cst816_init();
    // cst816_reset();
    ESP_LOGI(TAG, "id:%d\n", cst816_get_chip_id());
    while (1) {
        ESP_LOGI(TAG, "Main task running...%d", cst816_get_touch_point_num());
        a = gpio_get_level(GPIO_NUM_2);
        if (a != a_pre)
        {
            ESP_LOGI(TAG, "GPIO2 level: %d, pre = %d", a, a_pre);
        }
        a_pre = a;
        // ESP_LOGE(TAG, "Main task running...");
        // CST816_Get_XY_AXIS(); // 更新触摸坐标
        // if (CST816_Get_FingerNum() > 0) {
        //     ESP_LOGI(TAG, "Touch detected!");
        //     ESP_LOGI(TAG, "Touch X: %d, Y: %d", CST816_Instance.X_Pos, CST816_Instance.Y_Pos);
        // }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
