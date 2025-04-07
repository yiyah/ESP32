#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>
#include "driver/spi_master.h"

#define SPI_Transmit_data(handle, pdata, len)  SPI_Write_data(handle, pdata, len)

esp_err_t SPI_Write_cmd(spi_device_handle_t handle, uint8_t cmd);
esp_err_t SPI_Write_data(spi_device_handle_t handle, const uint8_t *data, int len);
esp_err_t SPI_Master_Init(uint16_t size_byte);


#endif
