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
    lcd_clear(LCD_COLOR_BLACK); // White
    lcd_set_pixel(0,0, LCD_COLOR_RED); // Red pixel at (0,0)
    lcd_set_pixel(LCD_HOR_RESOLUTION-1,0, LCD_COLOR_RED); // Red pixel at (0,0)
    lcd_set_pixel(0,LCD_VER_RESOLUTION-1, LCD_COLOR_RED); // Red pixel at (0,0)
    lcd_set_pixel(LCD_HOR_RESOLUTION-1,LCD_VER_RESOLUTION-1, LCD_COLOR_RED); // Red pixel at (0,0)
    lcd_flush();
    while (1) {
        ESP_LOGE(TAG, "Main task running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
