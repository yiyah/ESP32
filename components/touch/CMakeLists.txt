

idf_component_register(
    SRCS
        "cst816.c"
        "portable/cst816_esp.c"
    INCLUDE_DIRS
        "include"
        "portable"
    REQUIRES
        driver
)
