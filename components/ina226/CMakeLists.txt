

idf_component_register(
    SRCS
        "src/driver_ina226.c"
        "driver_ina226_basic.c"
        "driver_ina226_interface.c"
        "ina226.c"
    INCLUDE_DIRS
        "include"
    PRIV_INCLUDE_DIRS
        "src"
        "."
    REQUIRES
        common
        esp_driver_i2c
)
