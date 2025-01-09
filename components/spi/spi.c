#include "driver/gpio.h"
#include "spi.h"

#define SPI_HOST_NUM              SPI2_HOST

/* 引脚定义 */
#define SPI_MOSI_GPIO_PIN   GPIO_NUM_11         /* SPI2_MOSI */
#define SPI_CLK_GPIO_PIN    GPIO_NUM_12         /* SPI2_CLK */
#define SPI_MISO_GPIO_PIN   GPIO_NUM_13         /* SPI2_MISO */

esp_err_t SPI_Write_cmd(spi_device_handle_t handle, uint8_t cmd)
{
    spi_transaction_t t = {0};

    t.length = 8;                                       /* 要传输的位数 一个字节 8位 */
    t.tx_buffer = &cmd;                                 /* 将命令填充进去 */

    return spi_device_polling_transmit(handle, &t);     /* 开始传输 */
}

esp_err_t SPI_Write_data(spi_device_handle_t handle, const uint8_t *data, int len)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t t = {0};

    if (len != 0)
    {
        t.length = len * 8;                              /* 要传输的位数 一个字节 8位 */
        t.tx_buffer = data;                              /* 将命令填充进去 */
        ret = spi_device_polling_transmit(handle, &t);   /* 开始传输 */
    }
    else
    {
        /* keep ret = ESP_OK */
    }

    return ret;
}

esp_err_t SPI_Master_Init(uint16_t size_byte)
{
    spi_bus_config_t spi_bus_conf = {0};

    /* SPI总线配置 */
    spi_bus_conf.miso_io_num = SPI_MISO_GPIO_PIN;                               /* SPI_MISO引脚 */
    spi_bus_conf.mosi_io_num = SPI_MOSI_GPIO_PIN;                               /* SPI_MOSI引脚 */
    spi_bus_conf.sclk_io_num = SPI_CLK_GPIO_PIN;                                /* SPI_SCLK引脚 */
    spi_bus_conf.quadwp_io_num = -1;                                            /* SPI写保护信号引脚，该引脚未使能 */
    spi_bus_conf.quadhd_io_num = -1;                                            /* SPI保持信号引脚，该引脚未使能 */
    spi_bus_conf.max_transfer_sz = size_byte;                                   /* 配置最大传输大小，以字节为单位 */
    
    /* 初始化SPI总线 */
    return spi_bus_initialize(SPI_HOST_NUM, &spi_bus_conf, SPI_DMA_CH_AUTO);        /* SPI总线初始化 */
}
