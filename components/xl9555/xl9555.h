#ifndef __XL9555_H
#define __XL9555_H

typedef enum {
    XL9555_IO_DIR_OUTPUT = 0,
    XL9555_IO_DIR_INPUT = 1,
} XL9555_IO_DIRECTION;

#define IO_00_MASK                      ((uint16_t)1 << 0)
#define IO_01_MASK                      ((uint16_t)1 << 1)
#define IO_02_MASK                      ((uint16_t)1 << 2)
#define IO_03_MASK                      ((uint16_t)1 << 3)
#define IO_04_MASK                      ((uint16_t)1 << 4)
#define IO_05_MASK                      ((uint16_t)1 << 5)
#define IO_06_MASK                      ((uint16_t)1 << 6)
#define IO_07_MASK                      ((uint16_t)1 << 7)
#define IO_10_MASK                      ((uint16_t)1 << 8)
#define IO_11_MASK                      ((uint16_t)1 << 9)
#define IO_12_MASK                      ((uint16_t)1 << 10)
#define IO_13_MASK                      ((uint16_t)1 << 11)
#define IO_14_MASK                      ((uint16_t)1 << 12)
#define IO_15_MASK                      ((uint16_t)1 << 13)
#define IO_16_MASK                      ((uint16_t)1 << 14)
#define IO_17_MASK                      ((uint16_t)1 << 15)

#define BEEP_PIN                        IO_03_MASK
#define LCD_BL_PIN                      IO_10_MASK
#define KEY_0_PIN                       IO_17_MASK
#define KEY_1_PIN                       IO_16_MASK
#define KEY_2_PIN                       IO_15_MASK
#define KEY_3_PIN                       IO_14_MASK

void XL9555_Write_pin(uint16_t pin, uint8_t state);
uint8_t XL9555_Read_pin(uint16_t pin);
void XL9555_Config_GPIO(uint16_t pin, XL9555_IO_DIRECTION direction);
void XL9555_Init(void);



#endif
