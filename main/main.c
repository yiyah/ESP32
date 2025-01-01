#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

void app_main(void)
{
    LED_Init();

    while(1) {
        LED_TOGGLE();
        vTaskDelay(100);
    }
}
