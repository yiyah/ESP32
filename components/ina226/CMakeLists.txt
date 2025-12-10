

idf_component_register(
    SRCS
        "driver_ina226_interface.c"
        "driver_ina226.c"
    INCLUDE_DIRS
        "include"
        "."
    REQUIRES
        driver
        hs_common
)
