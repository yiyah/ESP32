/**
 * @file bsp_i2c.h
 *
 */

#ifndef BSP_I2C_H
#define BSP_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void i2c_init(void);
void i2c_found_device(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_I2C_H */
