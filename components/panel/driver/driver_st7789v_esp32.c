/**
 * @file driver_st7789v_esp32.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "esp_system.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"


#include "driver_st7789v_esp32.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    panel_t panel;      /*!< 继承 */

    /* io control */
    int backlight_io_num;
    int reset_io_num;
    int dc_io_num;
    int cs_io_num;

    /* spi */
    spi_host_device_t spi_host;
    int sclk_io_num;
    int mosi_io_num;
    int miso_io_num;

} st7789v_esp32_data_t;
/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static panel_ops_t st7789v_driver_ops = {
    .init = _init,
    .deinit = NULL,
    .draw_bitmap = NULL,
    .set_backlight = NULL,
};


static st7789v_esp32_data_t lcd = {
    .backlight_io_num = GPIO_NUM_21,
    .reset_io_num = GPIO_NUM_18,
    .dc_io_num = GPIO_NUM_16,
    .cs_io_num = GPIO_NUM_5,
    .spi_host = SPI2_HOST,
    .sclk_io_num = GPIO_NUM_14,
    .mosi_io_num = GPIO_NUM_13,
    .miso_io_num = GPIO_NUM_12,
};

/**********************`
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
panel_status_t driver_st7789v_init(void)
{
    panel_status_t ret = PANEL_OK;

    ret = panel_driver_register("st7789v",
                                &lcd.panel,
                                &st7789v_driver_ops);

    return ret;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static panel_status_t _init(const panel_handle_t handle)
{
    /* Initialization code specific to ST7789V on ESP32 platform */
    st7789v_esp32_data_t *data = (st7789v_esp32_data_t *)handle;
    return PANEL_OK;
}