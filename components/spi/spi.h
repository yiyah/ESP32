#ifndef __SPI_H
#define __SPI_H
#include "driver/spi_master.h"

esp_err_t SPI_Write_cmd(spi_device_handle_t handle, uint8_t cmd);
esp_err_t SPI_Write_data(spi_device_handle_t handle, const uint8_t *data, int len);
esp_err_t SPI_Master_Init(void);


#endif
