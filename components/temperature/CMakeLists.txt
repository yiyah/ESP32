

idf_component_register(
    SRCS
        "sht3x.c"
        "embedded-common/sensirion_common.c"
        "embedded-common/hw_i2c/sensirion_hw_i2c_implementation.c"
    INCLUDE_DIRS
        "include"
        "embedded-common"
    REQUIRES
)
