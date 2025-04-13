#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "iic.h"
#include "xl9555.h"
#include "spi.h"
#include "lcd.h"

void app_main(void)
{
    LED_Init();
    ESP_LOGW("MAIN", "LED_Init");
    ESP_ERROR_CHECK(IIC_Master_Init());
    ESP_LOGW("MAIN", "IIC_Init");
    XL9555_Init();
    ESP_LOGW("MAIN", "XL9555_Init");
    XL9555_Config_GPIO(BEEP_PIN, XL9555_IO_DIR_OUTPUT);
    XL9555_Config_GPIO(LCD_RST_PIN, XL9555_IO_DIR_OUTPUT);
    XL9555_Config_GPIO(LCD_PWR_PIN, XL9555_IO_DIR_OUTPUT);
    ESP_LOGW("MAIN", "CONFIG_GPIO");
    ESP_ERROR_CHECK(SPI_Master_Init(0));

    vLCD_Init();
    vLCD_SetDisplayDirection(LCD_DISP_LANDSCAPE);
    vLCD_Clear(LCD_COLOR_RED);
    uint16_t color = 0;
    vTaskDelay(500);
    // vLCD_SetDisplayDirection(LCD_DISP_PORTRAIT);
    vLCD_SetDisplayDirection(LCD_DISP_LANDSCAPE);
    LCD_vShow_ASCII_Char(12 + 0, 150, 'A', &afont16x8, LCD_COLOR_WHITE);
    LCD_vShow_ASCII_Char(12 + 8, 150, 'b', &afont16x8, LCD_COLOR_WHITE);
    LCD_vShow_ASCII_Char(12 + 16, 150, 'C', &afont16x8, LCD_COLOR_WHITE);
    LCD_vShow_ASCII_Char(12 + 24, 150, 'd', &afont16x8, LCD_COLOR_WHITE);
    LCD_vShow_Char(12 + 32, 150, 'e', &font24x32, LCD_COLOR_BLUE);
    LCD_vShow_Char(12 + 64, 150 + 0, 'F', &font24x32, LCD_COLOR_BLUE);
    LCD_vShow_Char(12 + 0, 150 + 32, 'F', &font24x32, LCD_COLOR_BLUE);
    while(1)
    {
        LED_TOGGLE();
        // XL9555_Write_pin(BEEP_PIN, data);
        // data = !data;
        // vLCD_Clear(color);
        // color = (color + 0x0100) & 0xFFFF;
        vTaskDelay(500);
    }
}
