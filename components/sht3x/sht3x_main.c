#include <stdio.h>
#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"
#include "sht3x_i2c.h"
#include "sht3x.h"
#define sensirion_hal_sleep_us sensirion_i2c_hal_sleep_usec

int16_t sht3x_main(void)
{
    int16_t error = NO_ERROR;
    sensirion_i2c_hal_init();
    sht3x_init(SHT30_I2C_ADDR_44);

    sht3x_stop_measurement();
    sensirion_hal_sleep_us(1000);
    sht3x_soft_reset();
    sensirion_hal_sleep_us(100000);
    uint16_t a_status_register = 0u;
    error = sht3x_read_status_register(&a_status_register);
    if (error != NO_ERROR) {
        printf("error executing read_status_register(): %i\n", error);
        return error;
    }
    printf("a_status_register: %02x\n", a_status_register);
    error = sht3x_start_periodic_measurement(REPEATABILITY_MEDIUM,
                                             MPS_ONE_PER_SECOND);
    if (error != NO_ERROR) {
        printf("error executing start_periodic_measurement(): %i\n", error);
        return error;
    }
    int32_t a_temperature = 0.0;
    int32_t a_humidity = 0.0;
    uint16_t repetition = 0;
    for (repetition = 0; repetition < 50; repetition++) {
        error = sht3x_blocking_read_measurement(&a_temperature, &a_humidity);
        if (error != NO_ERROR) {
            printf("error executing blocking_read_measurement(): %i\n", error);
            continue;
        }
        printf("a_temperature [milli degC]: %li ", a_temperature);
        printf("a_humidity [milli RH]: %li\n", a_humidity);
    }

    error = sht3x_stop_measurement();
    if (error != NO_ERROR) {
        return error;
    }
    return NO_ERROR;
}
