

set(srcs "bsp.c"
         "bsp_i2c.c")
set(includes "include")
set(priv_requires "esp_driver_i2c")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       PRIV_INCLUDE_DIRS "priv_include"
                       PRIV_REQUIRES ${priv_requires}
                       REQUIRES ${public_requires})
