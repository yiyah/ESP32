/**
 * @file port_cst816.h
 *
 */

#ifndef PORT_CST816_H
#define PORT_CST816_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "hs_err.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void port_gpio_init();
void port_iic_init();
hs_err_t port_iic_write_to_device(uint8_t reg, uint8_t data, size_t len);
hs_err_t port_iic_read_from_device(uint8_t reg, uint8_t* data, size_t len);
hs_err_t port_reset_pin_set_level(uint8_t level);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PORT_CST816_H */
