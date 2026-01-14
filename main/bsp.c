
extern void i2c_init(void);
extern void i2c_found_device(void);

void bsp_init(void)
{
    i2c_init();
    i2c_found_device();
}
