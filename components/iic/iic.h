#ifndef __IIC_H
#define __IIC_H
#include "driver/i2c.h"

esp_err_t IIC_Master_Init(void);
esp_err_t IIC_Write_Bytes(i2c_port_t i2c_num,
                        uint8_t    slave_addr,
                        uint8_t    slave_reg,
                        uint8_t    *data_wr,
                        size_t     size);
esp_err_t IIC_Read_Bytes(i2c_port_t i2c_num,
                        uint8_t    slave_addr,
                        uint8_t    slave_reg,
                        uint8_t    *data_rd,
                        size_t     size);
#endif
