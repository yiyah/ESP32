/**
 * @file cst816_esp.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "hs_err.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "CST816_PORT"

/**
 * @brief RESET 和 INT 引脚定义
 */
#define PIN_NUM_RESET           GPIO_NUM_37
#define PIN_NUM_INT             GPIO_NUM_2

#define RESET_ACTIVE_LEVEL      0
#define INT_ACTIVE_LEVEL        0

/**
 * @brief I2C 端口定义
 */

#define CST816_I2C_ADDR             0x15            /*!< not include read/write bit */
#define I2C_MASTER_SCL_IO           GPIO_NUM_42     /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           GPIO_NUM_41     /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0               /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000          /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0               /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0               /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
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
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void port_gpio_init()
{
    bool need_pullup = (RESET_ACTIVE_LEVEL == 0) ? true : false;

    /* 初始化 RESET PIN */
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << PIN_NUM_RESET,
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = need_pullup ? GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE,
        .pull_up_en = need_pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf);

    /* TODO: 初始化 INT PIN */
    need_pullup = (INT_ACTIVE_LEVEL == 0) ? true : false;
    io_conf.pin_bit_mask = 1ULL << PIN_NUM_INT;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.intr_type = (INT_ACTIVE_LEVEL == 0) ? GPIO_INTR_NEGEDGE : GPIO_INTR_POSEDGE;
    io_conf.pull_down_en = need_pullup ? GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = need_pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
}

void port_iic_init()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));

    ESP_LOGI(TAG, "I2C initialized successfully");
}

hs_err_t port_iic_write_to_device(uint8_t reg, uint8_t data, size_t len)
{
    return iic_write_bytes(I2C_MASTER_NUM, CST816_I2C_ADDR, reg, &data, len);
}

hs_err_t port_iic_read_from_device(uint8_t reg, uint8_t* data, size_t len)
{
    return iic_read_bytes(I2C_MASTER_NUM, CST816_I2C_ADDR, reg, data, len);
}

hs_err_t port_reset_pin_set_level(uint8_t level)
{
    return gpio_set_level(PIN_NUM_RESET, level);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
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
        ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret));
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

    if (data_len == 0) {
        ret = ESP_OK;
    } else {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        /* step1: write a register to slave to read */
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
        i2c_master_write_byte(cmd, reg_addr, true);

        /* step2: read byte from slave */
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
        if (data_len > 1) {
            i2c_master_read(cmd, pdata, data_len - 1, I2C_MASTER_ACK);
        }
        /* Read the last byte, we need to send a NACK
         * to prevent the slave device from continuing to send data.
         */
        i2c_master_read_byte(cmd, pdata + data_len - 1, I2C_MASTER_NACK);
        i2c_master_stop(cmd);

        ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
    }

    return ret;
}
