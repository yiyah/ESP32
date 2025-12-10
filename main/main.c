#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "app_button.h"
#include "panel.h"
#include "cst816.h"
#include "driver/gpio.h"
#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"
#include "sht3x_i2c.h"
#include "driver_ina226.h"
#include "driver_ina226_interface.h"
#include "driver/i2c.h"
#include "esp_log.h"

#define TAG "main"
#define sensirion_hal_sleep_us sensirion_i2c_hal_sleep_usec

volatile int a = 0;
static ina226_handle_t gs_handle;        /**< ina226 handle */

void i2c_scan(i2c_port_t i2c_num)
{
    ESP_LOGI("I2C_SCAN", "Scanning I2C bus %d ...", i2c_num);
    for (int addr = 1; addr < 127; addr++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(50));
        i2c_cmd_link_delete(cmd);
        if (ret == ESP_OK) {
            ESP_LOGI("I2C_SCAN", "Found device at 0x%02x", addr);
        }
    }
}

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
//     extern void port_iic_init();
// port_iic_init();
//     i2c_scan(0);
    /* link interface function */
    DRIVER_INA226_LINK_INIT(&gs_handle, ina226_handle_t);
    DRIVER_INA226_LINK_IIC_INIT(&gs_handle, ina226_interface_iic_init);
    DRIVER_INA226_LINK_IIC_DEINIT(&gs_handle, ina226_interface_iic_deinit);
    DRIVER_INA226_LINK_IIC_READ(&gs_handle, ina226_interface_iic_read);
    DRIVER_INA226_LINK_IIC_WRITE(&gs_handle, ina226_interface_iic_write);
    DRIVER_INA226_LINK_DELAY_MS(&gs_handle, ina226_interface_delay_ms);
    DRIVER_INA226_LINK_DEBUG_PRINT(&gs_handle, ina226_interface_debug_print);
    DRIVER_INA226_LINK_RECEIVE_CALLBACK(&gs_handle, ina226_interface_receive_callback);

    /* set addr pin */
    uint8_t res;
    res = ina226_set_addr_pin(&gs_handle, 0x40);
    if (res != 0)
    {
        ina226_interface_debug_print("ina226: set addr pin failed.\n");
       
    }
        ina226_interface_debug_print("ina226: set addr pin success.\n");

    /* set the r */
    res = ina226_set_resistance(&gs_handle, 0.05);
    if (res != 0)
    {
        ina226_interface_debug_print("ina226: set resistance failed.\n");
       
    }
    
    /* init */
    res = ina226_init(&gs_handle);
    if (res != 0)
    {
        ina226_interface_debug_print("ina226: init failed.\n");
       
    }
    // cst816_init();
    // ESP_LOGI(TAG, "id:%d\n", cst816_get_chip_id());

    // sensirion_i2c_hal_init();
    // sht3x_init(SHT30_I2C_ADDR_44);
    // sht3x_stop_measurement();
    // sensirion_hal_sleep_us(1000);
    // sht3x_soft_reset();
    // sensirion_hal_sleep_us(100000);
    //     uint16_t a_status_register = 0u;
    // int16_t error = NO_ERROR;
    // error = sht3x_read_status_register(&a_status_register);
    // if (error != NO_ERROR) {
    //     printf("error executing read_status_register(): %i\n", error);
    //     // return error;
    // }
    // printf("a_status_register: %02x\n", a_status_register);
    // error = sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM,
    //                                          MPS_ONE_PER_SECOND);
    // if (error != NO_ERROR) {
    //     printf("error executing start_periodic_measurement(): %i\n", error);
    //     // return error;
    // }
    // int32_t a_temperature = 0.0;
    // int32_t a_humidity = 0.0;
    // uint16_t repetition = 0;
    // for (repetition = 0; repetition < 50; repetition++) {
    //     error = sht3x_blocking_read_measurement(&a_temperature, &a_humidity);
    //     if (error != NO_ERROR) {
    //         printf("error executing blocking_read_measurement(): %i\n", error);
    //         continue;
    //     }
    //     printf("a_temperature [milli degC]: %li ", a_temperature);
    //     printf("a_humidity [milli RH]: %li\n", a_humidity);
    // }

    // error = sht3x_stop_measurement();
    // if (error != NO_ERROR) {
    //     // return error;
    // }

    vTaskDelay(pdMS_TO_TICKS(2000));
    uint16_t x, y;
    while (1) {
        // ESP_LOGI(TAG, "Main task running...%d", cst816_get_touch_point_num());
        // ESP_LOGW(TAG, "GPIO2 level: %d", gpio_get_level(GPIO_NUM_2));
        if (a == 1)
        {
            a = 0;
            uint8_t ss = gpio_get_level(GPIO_NUM_2);
            cst816_get_touch_point(&x, &y);
            ESP_LOGI(TAG, "GPIO2 level: %d",ss);
            // ESP_LOGI(TAG, "X: %d, y: %d", x, y);
        }
        // ESP_LOGE(TAG, "Main task running...");
        // CST816_Get_XY_AXIS(); // 更新触摸坐标
        // if (CST816_Get_FingerNum() > 0) {
        //     ESP_LOGI(TAG, "Touch detected!");
        //     ESP_LOGI(TAG, "Touch X: %d, Y: %d", CST816_Instance.X_Pos, CST816_Instance.Y_Pos);
        // }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
