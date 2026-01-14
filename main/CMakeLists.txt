set(srcs "main.c"
        "app_task.c")

idf_component_register(
    SRCS
        ${srcs}
    INCLUDE_DIRS
        "."
    REQUIRES
        bsp
        common
        sht3x
        ina226
)
