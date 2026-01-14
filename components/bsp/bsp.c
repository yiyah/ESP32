#include "bsp_i2c.h"


void bsp_init(void)
{
    i2c_init();
    i2c_found_device();
}
