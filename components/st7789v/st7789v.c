#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "../spi/spi.h"
#include "../xl9555/xl9555.h"
#include "st7789v.h"

/**
 * 2.4' LCD
 * resolution: 240(H) * 320(V)
 * 4-Line SPI: DC, SCL, SDA, CS
 */

/**
 * About ST7789V
 * @Display resolution: 240(H) * 320(V)
 * @Frame RAM Size: 240*320*18 bit = 1,382,400 bits = 172,800 bytes
 * 
 * @Power-Up Timing:
 *   RST   _____             _________________
 *              |___________|
 *              | t > 10us  |   t > 120ms    |
 * @protocol
 *   D7-D0: D7 first
 * @CMD
 *   MADCTR: MX, MY
 *   
 */


#define REG_MADCTL      0x36u /* Memory Data Access Control register */

#define ST7789V_PIN_DC  GPIO_NUM_40
#define ST7789V_PIN_CS  GPIO_NUM_21


#define GPIO_RST(x)     do { \
                            (x) \
                            ? (XL9555_Write_pin(LCD_RST_PIN, 1)) \
                            : (XL9555_Write_pin(LCD_RST_PIN, 0)); \
                        } while(0)

#define GPIO_WR(x)     do { \
                            gpio_set_level(ST7789V_PIN_DC, (x)); \
                        } while(0)


spi_device_handle_t ST7789V_handle;

static void vHardware_Reset(void)
{
    GPIO_RST(0);
    vTaskDelay(100);
    GPIO_RST(1);
    vTaskDelay(100);
}

static void vGPIO_Init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ST7789V_PIN_DC),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
}

uint8_t u8ST7789V_Write_CMD(uint8_t cmd)
{
    GPIO_WR(0);
    return SPI_Transmit_data(ST7789V_handle, &cmd, 1);
}

uint8_t u8ST7789V_Write_DATA(uint8_t *pu8data, uint16_t u16len)
{
    GPIO_WR(1);
    return SPI_Transmit_data(ST7789V_handle, pu8data, u16len);
}

uint8_t u8ST7789V_SetScanDirection(ST7789V_SCAN_DIRECTION dir, uint8_t u8XY_Exchange)
{
    uint8_t u8data = 0;

    switch (dir)
    {
        case ST7789V_SCAN_LRUD:
            u8data = 0x00;
            break;
        case ST7789V_SCAN_RLUD:
            u8data = 0x60;
            break;
        case ST7789V_SCAN_LRDU:
            u8data = 0xC0;
            break;
        case ST7789V_SCAN_RLDU:
            u8data = 0xA0;
            break;
        default:
            break;
    }

    return u8ST7789V_Write_CMD(REG_MADCTL) || u8ST7789V_Write_DATA(&u8data, 1);
}

void ST7789V_Init(void)
{
    esp_err_t ret = ESP_OK;
    uint8_t u8data = 0;

    // 初始化 DC IO
    vGPIO_Init();

    // 添加SPI总线设备
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 60 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = ST7789V_PIN_CS,
        .queue_size = 7,
    };
    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &ST7789V_handle);
    ESP_ERROR_CHECK(ret);

    // 复位 ST7789V
    vHardware_Reset();

    // 初始化
    u8ST7789V_Write_CMD(CMD_SLPOUT);
    vTaskDelay(120);

    u8ST7789V_Write_CMD(CMD_MADCTL);
    u8data = 0U;
    u8ST7789V_Write_DATA(&u8data, 1);

    u8ST7789V_Write_CMD(CMD_COLMOD);
    u8ST7789V_Write_DATA((uint8_t[]){COLMOD_65K_16BIT}, 1);

    u8ST7789V_Write_CMD(CMD_INVON);
    vTaskDelay(120);

    u8ST7789V_Write_CMD(CMD_DISPON);
    vTaskDelay(120);
}
