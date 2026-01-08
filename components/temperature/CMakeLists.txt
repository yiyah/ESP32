

idf_component_register(
    SRCS
        "sensirion_common.c"
        "sensirion_i2c_hal.c"
        "sensirion_i2c_gpio.c"
        "sensirion_i2c.c"
        "sht3x_i2c.c"
    INCLUDE_DIRS
        "include"
        "."
    REQUIRES
        driver
        hs_common
)
