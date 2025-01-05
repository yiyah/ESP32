#include <stdio.h>
#include "driver/gpio.h"
#include "iic.h"

/* Define IIC master parameters */
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_SCL_IO           GPIO_NUM_42         /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO           GPIO_NUM_41         /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ          400000              /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                   /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                   /*!< I2C master doesn't need buffer */
#define WRITE_BIT                   I2C_MASTER_WRITE    /*!< I2C master write */
#define READ_BIT                    I2C_MASTER_READ     /*!< I2C master read */
#define ACK_CHECK_EN                0x1                 /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS               0x0                 /*!< I2C master will not check ack from slave */
#define ACK_VAL                     0x0                 /*!< I2C ack value */
#define NACK_VAL                    0x1                 /*!< I2C nack value */

/**
 * @brief test code to read esp-i2c-slave
 *        We need to fill the buffer of esp slave device, then master can read them out.
 *
 * __________________________________________________________________________________________________________
 * | start | slave_addr + rd_bit + ack | slave_reg + ack | read n-1 bytes + ack | read 1 byte + nack | stop |
 * --------|---------------------------|-----------------|----------------------|--------------------|------|
 *
 * @note cannot use master read slave on esp32c3 because there is only one i2c controller on esp32c3
 */
esp_err_t __attribute__((unused)) IIC_Read_Bytes(i2c_port_t i2c_num,
                                                 uint8_t    slave_addr,
                                                 uint8_t    slave_reg,
                                                 uint8_t    *data_rd,
                                                 size_t     size)
{
    esp_err_t ret = ESP_OK;

    if (size == 0)
    {
        ret = ESP_OK;
    }
    else
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        /* step1: write a register to slave to read */
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (slave_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
        i2c_master_write_byte(cmd, slave_reg, ACK_CHECK_EN);

        /* step2: read byte from slave */
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (slave_addr << 1) | READ_BIT, ACK_CHECK_EN);
        if (size > 1) {
            i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
        }
        /* Read the last byte, we need to send a NACK
         * to prevent the slave device from continuing to send data.
         */
        i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
        i2c_master_stop(cmd);

        ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
    }

    return ret;
}

/**
 * @brief Test code to write esp-i2c-slave
 *        Master device write data to slave(both esp32),
 *        the data will be stored in slave buffer.
 *        We can read them out from slave buffer.
 *
 * _____________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | slave_reg + ack | write n bytes + ack  | stop |
 * --------|---------------------------|-----------------|----------------------|------|
 *
 * @note cannot use master write slave on esp32c3 because there is only one i2c controller on esp32c3
 */
esp_err_t __attribute__((unused)) IIC_Write_Bytes(i2c_port_t i2c_num,
                                                  uint8_t    slave_addr,
                                                  uint8_t    slave_reg,
                                                  uint8_t    *data_wr,
                                                  size_t     size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, slave_reg, ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t IIC_Master_Init(void)
{
    i2c_port_t i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
