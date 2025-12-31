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
    panel_t base;      /*!< 继承 */

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

    esp_lcd_panel_handle_t panel_handle;
    esp_lcd_panel_io_handle_t io_handle;
} st7789_panel_t;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static panel_status_t _init(const panel_handle_t handle);
static panel_status_t _set_backlight(const panel_handle_t handle, bool on);
static panel_status_t _draw_bitmap(const panel_handle_t handle, int x, int y, int w, int h, const uint8_t *data);

/**********************
 *  STATIC VARIABLES
 **********************/

static panel_ops_t s_st7789v_driver_ops = {
    .init = _init,
    .deinit = NULL,
    .draw_bitmap = _draw_bitmap,
    .set_backlight = _set_backlight,
};


static st7789_panel_t s_st7789 = {
    .backlight_io_num = PIN_NUM_BCKL,
    .reset_io_num = PIN_NUM_RST,
    .dc_io_num = PIN_NUM_DC,
    .cs_io_num = PIN_NUM_CS,
    .spi_host = LCD_HOST,
    .sclk_io_num = PIN_NUM_CLK,
    .mosi_io_num = PIN_NUM_MOSI,
    .miso_io_num = PIN_NUM_MISO,
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
                                &s_st7789.base,
                                &s_st7789v_driver_ops);

    return ret;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static panel_status_t _init(const panel_handle_t handle)
{
    panel_status_t ret = PANEL_OK;
    /* Initialization code specific to ST7789V on ESP32 platform */
    st7789_panel_t *st7789 = (st7789_panel_t *)handle;

    /* 初始化背光，和SPI无关的IO */
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << st7789->backlight_io_num
    };
    // Initialize the GPIO of backlight
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    /* 初始化 spi 总线相关的IO */
    spi_bus_config_t buscfg = {
        .sclk_io_num = st7789->sclk_io_num,
        .mosi_io_num = st7789->mosi_io_num,
        .miso_io_num = st7789->miso_io_num,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = MAX_TRANSFER_SIZE(st7789->base.cfg.height)
    };
    ESP_ERROR_CHECK(spi_bus_initialize(st7789->spi_host, &buscfg, SPI_DMA_CH_AUTO));

    /* 初始化和SPI相关的 IO，非SPI总线的 */
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = st7789->dc_io_num,
        .cs_gpio_num = st7789->cs_io_num,
        .pclk_hz = LCD_SPI_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)st7789->spi_host, &io_config, &st7789->io_handle));

    /* 初始化 LCD panel 相关的 IO */
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = st7789->reset_io_num,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    // Initialize the LCD configuration
    /* install st7789 driver */
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(st7789->io_handle, &panel_config, &st7789->panel_handle));

    // Turn off backlight to avoid unpredictable display on the LCD screen while initializing
    // the LCD panel driver. (Different LCD screens may need different levels)
    ESP_ERROR_CHECK(gpio_set_level(st7789->backlight_io_num, LCD_BK_LIGHT_OFF_LEVEL));

    // Reset the display
    ESP_ERROR_CHECK(esp_lcd_panel_reset(st7789->panel_handle));

    // Initialize LCD panel
    ESP_ERROR_CHECK(esp_lcd_panel_init(st7789->panel_handle));

    // Turn on the screen
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(st7789->panel_handle, true));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(st7789->panel_handle, LCD_INVERT_COLOR));
    // Swap x and y axis (Different LCD screens may need different options)
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(st7789->panel_handle, true));

    esp_lcd_panel_set_gap(st7789->panel_handle, LCD_GAP_X, LCD_GAP_Y);
    // Turn on backlight (Different LCD screens may need different levels)
    ESP_ERROR_CHECK(gpio_set_level(st7789->backlight_io_num, LCD_BK_LIGHT_ON_LEVEL));
    
    return ret;
}

static panel_status_t _set_backlight(const panel_handle_t handle, bool on)
{
    esp_err_t ret = ESP_OK;
    st7789_panel_t *st7789 = (st7789_panel_t *)handle;

    ret = gpio_set_level(st7789->backlight_io_num, on ? LCD_BK_LIGHT_ON_LEVEL : LCD_BK_LIGHT_OFF_LEVEL);
    
    return ret == ESP_OK ? PANEL_OK : PANEL_ERR_IO;
}

static panel_status_t _draw_bitmap(const panel_handle_t handle, int x, int y, int w, int h, const uint8_t *data)
{
    esp_err_t ret = ESP_OK;
    st7789_panel_t *st7789 = (st7789_panel_t *)handle;

    ret = esp_lcd_panel_draw_bitmap(st7789->panel_handle, x, y, x + w - 1, y + h - 1, data);

    return ret == ESP_OK ? PANEL_OK : PANEL_ERR_UNKNOWN;
}