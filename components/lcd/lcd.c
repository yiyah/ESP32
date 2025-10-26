/**
 * @file lcd.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "font.h"
#include "lcd.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct lcd
{
    uint16_t gram[LCD_HOR_RESOLUTION * LCD_VER_RESOLUTION];
    const ASCIIFont* font;
    esp_lcd_panel_handle_t panel_handle;

    struct
    {
        uint16_t fore;
        uint16_t back;
    } color;
    
    struct
    {
        uint16_t x;
        uint16_t y;
    } point;
} lcd_t;
 /**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lcd_t lcd;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lcd_printf(const char* str)
{

}

/**
 * 列行式字库打印
 */
void lcd_printf_ascii(uint8_t ascii)
{
    uint8_t char_index = ascii - ' ';
    uint32_t index = (lcd.point.y * LCD_COLS + lcd.point.x) * 2;

    for (uint8_t i = 0; i < lcd.font->h; i++) {
        for (uint8_t j = 0; j < lcd.font->w; j++) {
            uint8_t byte = lcd.font->chars[char_index * lcd.font->h + i];
            if (byte & (0x80 >> (j % 8))) {
                lcd.gram[index + 0] = 0xFF;
                lcd.gram[index + 1] = 0xFF;
            } else {
                lcd.gram[index + 0] = 0x00;
                lcd.gram[index + 1] = 0x00;
            }
            index += 2;
        }
        index += (LCD_COLS - lcd.font->w) * 2;
    }
}

/**
 * x: 0 ~ LCD_HOR_RESOLUTION-1
 * y: 0 ~ LCD_VER_RESOLUTION-1
 */
void lcd_set_pixel(uint16_t x, uint16_t y, uint16_t color565)
{
    uint32_t index = y * LCD_COLS + x;
    lcd.gram[index] = color565;
}

void lcd_flush(void)
{
    esp_lcd_panel_draw_bitmap(lcd.panel_handle, 0, 0 , LCD_HOR_RESOLUTION, LCD_VER_RESOLUTION, lcd.gram);
}

void lcd_clear(uint16_t color565)
{
    for (uint32_t i = 0; i < sizeof(lcd.gram); i++) {
        lcd.gram[i] = color565;
    }
    // esp_lcd_panel_draw_bitmap(lcd.panel_handle, 0, 0 , LCD_HOR_RESOLUTION - 1, LCD_VER_RESOLUTION - 1, lcd.gram);
}

void lcd_init(void)
{
    /* 初始化背光，和SPI无关的IO */
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << PIN_NUM_BCKL
    };
    // Initialize the GPIO of backlight
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    /* 初始化 spi 总线相关的IO */
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_CLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = MAX_TRANSFER_SIZE
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    /* 初始化和SPI相关的 IO，非SPI总线的 */
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_NUM_DC,
        .cs_gpio_num = PIN_NUM_CS,
        .pclk_hz = LCD_SPI_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    /* 初始化 LCD panel 相关的 IO */
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    // Initialize the LCD configuration
    /* install st7789 driver */
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &lcd.panel_handle));

    // Turn off backlight to avoid unpredictable display on the LCD screen while initializing
    // the LCD panel driver. (Different LCD screens may need different levels)
    ESP_ERROR_CHECK(gpio_set_level(PIN_NUM_BCKL, LCD_BK_LIGHT_OFF_LEVEL));

    // Reset the display
    ESP_ERROR_CHECK(esp_lcd_panel_reset(lcd.panel_handle));

    // Initialize LCD panel
    ESP_ERROR_CHECK(esp_lcd_panel_init(lcd.panel_handle));

    // Turn on the screen
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(lcd.panel_handle, true));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(lcd.panel_handle, true));

    // Swap x and y axis (Different LCD screens may need different options)
    // ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(lcd.panel_handle, true));

    esp_lcd_panel_set_gap(lcd.panel_handle, 52, 40);

    // Turn on backlight (Different LCD screens may need different levels)
    ESP_ERROR_CHECK(gpio_set_level(PIN_NUM_BCKL, LCD_BK_LIGHT_ON_LEVEL));

    lcd_clear(0x001F);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
