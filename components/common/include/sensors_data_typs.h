/**
 * @file sensors_data_typs.h
 *
 */

#ifndef SENSOR_DATA_TYPES_H
#define SENSOR_DATA_TYPES_H

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
typedef struct {
    float voltage;    /**< Voltage in mV */
    float current;    /**< Current in mA */
    float power;      /**< Power in mW */
} ina226_data_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SENSOR_DATA_TYPES_H */
