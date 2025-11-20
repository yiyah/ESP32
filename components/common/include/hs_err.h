/**
 * @file hs_err.h
 *
 */

#ifndef HS_ERR_H
#define HS_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/
#define HS_OK                  0       /*!< success */
#define HS_FAIL                -1      /*!< generic error */

/**********************
 *      TYPEDEFS
 **********************/
typedef int hs_err_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* HS_ERR_H */
