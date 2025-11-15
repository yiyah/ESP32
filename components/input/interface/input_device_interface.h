/**
 * @file lv_templ.h
 *
 */

#ifndef INPUT_DEVICE_INTERFACE_H
#define INPUT_DEVICE_INTERFACE_H

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
typedef input_device_interface_t input_device_interface_t;

struct input_device_interface_t
{
    void (*init)(void);
    void (*read)(void);
};
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*INPUT_DEVICE_INTERFACE_H*/