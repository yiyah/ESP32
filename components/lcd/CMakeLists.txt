
file(GLOB FONT_SRCS "${CMAKE_CURRENT_LIST_DIR}/font/*.c")



idf_component_register(
    SRCS
        "panel.c"
        "portable/st7789_esp.c"
        ${FONT_SRCS}

    INCLUDE_DIRS
        "include"
        "font"
        "portable"
    REQUIRES
        driver
        esp_lcd
)
