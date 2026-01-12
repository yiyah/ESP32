

idf_component_register(
    SRCS
        "sht3x_main.c"
        "lib/sensirion_common.c"
        "sensirion_i2c_hal.c"
        "lib/sensirion_i2c.c"
        "lib/sht3x_i2c.c"
    INCLUDE_DIRS
        "include"
    REQUIRES
    PRIV_REQUIRES
        esp_driver_i2c
)
