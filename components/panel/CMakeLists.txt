

idf_component_register(
    SRCS
        "src/lcd.c"
        "interface/panel.c"
        "driver/driver_st7789v_esp32.c"
    INCLUDE_DIRS
        "include"
        "interface"
        "driver"
    REQUIRES
        driver
        esp_lcd
)
