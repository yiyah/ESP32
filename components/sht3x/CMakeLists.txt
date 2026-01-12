

idf_component_register(
    SRCS
        "sht3x_main.c"
        "sensirion_i2c_hal.c"
        "lib/sensirion_i2c.c"
        "lib/sensirion_common.c"
        "lib/sht3x_i2c.c"
    INCLUDE_DIRS
        "include"
    PRIV_INCLUDE_DIRS
        "lib"
    REQUIRES
        driver
        esp_driver_i2c
)
