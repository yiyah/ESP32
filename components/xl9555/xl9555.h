#ifndef __XL9555_H
#define __XL9555_H

typedef enum {
    XL9555_IO_DIR_OUTPUT = 0,
    XL9555_IO_DIR_INPUT = 1,
} XL9555_IO_DIRECTION;

#define IO_IN_LOW_REG_MASK              ((uint16_t)0U << 8)
#define IO_IN_HIG_REG_MASK              ((uint16_t)1U << 8)
#define IO_00_MASK                      (IO_IN_LOW_REG_MASK | (1U << 0))
#define IO_01_MASK                      (IO_IN_LOW_REG_MASK | (1U << 1))
#define IO_02_MASK                      (IO_IN_LOW_REG_MASK | (1U << 2))
#define IO_03_MASK                      (IO_IN_LOW_REG_MASK | (1U << 3))
#define IO_04_MASK                      (IO_IN_LOW_REG_MASK | (1U << 4))
#define IO_05_MASK                      (IO_IN_LOW_REG_MASK | (1U << 5))
#define IO_06_MASK                      (IO_IN_LOW_REG_MASK | (1U << 6))
#define IO_07_MASK                      (IO_IN_LOW_REG_MASK | (1U << 7))
#define IO_10_MASK                      (IO_IN_HIG_REG_MASK | (1U << 0))
#define IO_11_MASK                      (IO_IN_HIG_REG_MASK | (1U << 1))
#define IO_12_MASK                      (IO_IN_HIG_REG_MASK | (1U << 2))
#define IO_13_MASK                      (IO_IN_HIG_REG_MASK | (1U << 3))
#define IO_14_MASK                      (IO_IN_HIG_REG_MASK | (1U << 4))
#define IO_15_MASK                      (IO_IN_HIG_REG_MASK | (1U << 5))
#define IO_16_MASK                      (IO_IN_HIG_REG_MASK | (1U << 6))
#define IO_17_MASK                      (IO_IN_HIG_REG_MASK | (1U << 7))

#define KEY_0_PIN                        IO_17_MASK
#define KEY_1_PIN                        IO_16_MASK
#define KEY_2_PIN                        IO_15_MASK
#define KEY_3_PIN                        IO_14_MASK
#define BEEP_PIN                         IO_03_MASK

void XL9555_Write_pin(uint16_t pin, uint8_t state);
uint8_t XL9555_Read_pin(uint16_t pin);
void XL9555_Config_GPIO(uint16_t pin, XL9555_IO_DIRECTION direction);
void XL9555_Init(void);



#endif
