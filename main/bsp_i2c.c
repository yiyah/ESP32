/**
 * @file bsp_i2c.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
/*********************
 *      DEFINES
 *********************/
#define TEST_I2C_PORT I2C_NUM_0
#define I2C_MASTER_SCL_IO 5
#define I2C_MASTER_SDA_IO 4


#define TAG "bsp_i2c"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

 /**********************
 *   GLOBAL FUNCTIONS
 **********************/

void i2c_init(void)
{
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = TEST_I2C_PORT,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
}

void i2c_found_device(void)
{
    for (uint16_t addr = 1; addr < 127; addr++) 
    {
        if (i2c_master_probe(bus_handle, addr, 1000) == ESP_OK) {
            ESP_LOGI(TAG, "Found I2C device at address 0x%02X", addr);
        }
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

