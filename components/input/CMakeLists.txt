

idf_component_register(
    SRCS
        "src/cst816.c"
        "src/iic_hal.c"
    INCLUDE_DIRS
        "include"
    REQUIRES
        driver
)
