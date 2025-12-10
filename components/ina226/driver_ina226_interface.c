/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ina226_interface_template.c
 * @brief     driver ina226 interface template source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-01-29
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/01/29  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
#include <stdarg.h>
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdarg.h>
#include <stdio.h>
#include "driver_ina226_interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "ina226_interface"

/**
 * @brief I2C 端口定义
 */

#define I2C_ADDR             0x40            /*!< 7-bit I2C address (not include read/write bit) */
#define I2C_MASTER_SCL_IO           GPIO_NUM_42     /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           GPIO_NUM_41     /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0               /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000          /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0               /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0               /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

static esp_err_t iic_write_bytes(i2c_port_t i2c_num,
                                 uint8_t    dev_addr,
                                 uint8_t    reg_addr,
                                 uint8_t*   pdata,
                                 size_t     data_len);
static esp_err_t iic_read_bytes(i2c_port_t  i2c_num,
                                uint8_t     dev_addr,
                                uint8_t     reg_addr,
                                uint8_t*    pdata,
                                size_t      data_len);
/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t ina226_interface_iic_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    ESP_LOGI(TAG, "Configuring I2C: SCL=%d, SDA=%d, freq=%d", I2C_MASTER_SCL_IO, I2C_MASTER_SDA_IO, I2C_MASTER_FREQ_HZ);
    
    esp_err_t ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C param config failed: %s", esp_err_to_name(ret));
        return 1;
    }
    
    ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C driver install failed: %s", esp_err_to_name(ret));
        return 1;
    }

    ESP_LOGI(TAG, "I2C initialized successfully");
    return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t ina226_interface_iic_deinit(void)
{
    return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr iic device write address
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ina226_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return iic_read_bytes(I2C_MASTER_NUM, addr, reg, buf, len) == 0 ? 0 : 1;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr iic device write address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ina226_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return iic_write_bytes(I2C_MASTER_NUM, addr, reg, buf, len) == 0 ? 0 : 1;
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void ina226_interface_delay_ms(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void ina226_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf((char *)str, sizeof(str), fmt, args);
    printf("%s", (char *)str);
    va_end(args);
}

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 * @note      none
 */
void ina226_interface_receive_callback(uint8_t type)
{
    switch (type)
    {
        case INA226_STATUS_SHUNT_VOLTAGE_OVER_VOLTAGE :
        {
            ina226_interface_debug_print("ina226: irq shunt voltage over voltage.\n");
            
            break;
        }
        case INA226_STATUS_SHUNT_VOLTAGE_UNDER_VOLTAGE :
        {
            ina226_interface_debug_print("ina226: irq shunt voltage under voltage.\n");
            
            break;
        }
        case INA226_STATUS_BUS_VOLTAGE_OVER_VOLTAGE :
        {
            ina226_interface_debug_print("ina226: irq bus voltage over voltage.\n");
            
            break;
        }
        case INA226_STATUS_BUS_VOLTAGE_UNDER_VOLTAGE :
        {
            ina226_interface_debug_print("ina226: irq bus voltage under voltage.\n");
            
            break;
        }
        case INA226_STATUS_POWER_OVER_LIMIT :
        {
            ina226_interface_debug_print("ina226: irq power over limit.\n");
            
            break;
        }
        default :
        {
            ina226_interface_debug_print("ina226: unknown code.\n");
            
            break;
        }
    }
}


static esp_err_t iic_write_bytes(i2c_port_t i2c_num, uint8_t dev_addr, uint8_t reg_addr, uint8_t* pdata, size_t data_len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, pdata, data_len, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C write failed (dev=0x%02x, reg=0x%02x, len=%d): %s", dev_addr, reg_addr, data_len, esp_err_to_name(ret));
    } else {
        ESP_LOGD(TAG, "I2C write success (dev=0x%02x, reg=0x%02x, len=%d)", dev_addr, reg_addr, data_len);
    }
    i2c_cmd_link_delete(cmd);

    return ret;
}

static esp_err_t iic_read_bytes(i2c_port_t  i2c_num,
                                uint8_t     dev_addr,
                                uint8_t     reg_addr,
                                uint8_t*    pdata,
                                size_t      data_len)
{
    esp_err_t ret = ESP_OK;
    ESP_LOGD(TAG, "iic_read_bytes: dev_addr=0x%02x, reg_addr=0x%02x, len=%d", dev_addr, reg_addr, data_len);

    if (data_len == 0) {
        ret = ESP_OK;
    } else {
        /* Step 1: Write register address */
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, reg_addr, true);
        i2c_master_stop(cmd);

        ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
        i2c_cmd_link_delete(cmd);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "I2C write reg addr failed (dev=0x%02x, reg=0x%02x): %s", dev_addr, reg_addr, esp_err_to_name(ret));
            return ret;
        }
        /* Small delay to allow slave device to process register pointer */
        vTaskDelay(pdMS_TO_TICKS(5));
        
        /* Step 2: Read data */
        cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
        
        if (data_len > 1) {
            i2c_master_read(cmd, pdata, data_len - 1, I2C_MASTER_ACK);
        }
        i2c_master_read_byte(cmd, pdata + data_len - 1, I2C_MASTER_NACK);
        i2c_master_stop(cmd);

        ret = i2c_master_cmd_begin(i2c_num, cmd, pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "I2C read data failed (dev=0x%02x, reg=0x%02x, len=%d): %s", dev_addr, reg_addr, data_len, esp_err_to_name(ret));
        } else {
            ESP_LOGD(TAG, "I2C read success (dev=0x%02x, reg=0x%02x, len=%d)", dev_addr, reg_addr, data_len);
        }

        i2c_cmd_link_delete(cmd);
    }

    return ret;
}
