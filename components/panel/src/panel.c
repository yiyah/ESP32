/**
 * @file panel.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include "panel.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static panel_handle_t _find_driver_handle(const char* find_which);
static bool check_driver_had_register(const char* driver_name);

/**********************
 *  STATIC VARIABLES
 **********************/
static panel_handle_t s_panel_handle_list = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
panel_status_t panel_init(const char* driver_name, panel_handle_t *handle_out, panel_config_t* config)
{
    panel_status_t ret = PANEL_OK;

    if (driver_name == NULL) {
        return PANEL_ERR_INVALID_ARG;
    }

    panel_handle_t found = _find_driver_handle(driver_name);
    if (found == NULL) {
        return PANEL_ERR_UNKNOWN;
    }

    if (found->ops == NULL || found->ops->init == NULL) {
        return PANEL_ERR_UNSUPPORTED;
    }

    /* apply config if provided */
    if (config) {
        found->cfg = *config;
    }

    ret = found->ops->init(found);
    if (ret == PANEL_OK && handle_out != NULL) {
        *handle_out = found;
    }

    return ret;
}

/**
 * 
 * step1: no driver
 *        s_panel_handle_list == NULL
 * step2: register 1 driver
 *        s_panel_handle_list -> driver1 -> NULL
 * step3: register 2 driver
 *        s_panel_handle_list -> driver2 -> driver1 -> NULL
 */
panel_status_t panel_driver_register(const char* driver_name,
                                     const panel_handle_t handle,
                                     const panel_ops_t* ops)
{
    panel_status_t ret = PANEL_OK;

    if (check_driver_had_register(driver_name)) {
        ret = PANEL_ERR_INVALID_ARG;
    } else {
        handle->driver_name = driver_name;
        handle->ops = ops;

        handle->next = s_panel_handle_list;
        s_panel_handle_list = handle;
        ret = PANEL_OK;
    }

    return ret;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * 
 * @retval true:  found
 *         false: not found
 */
static bool check_driver_had_register(const char* driver_name)
{
    bool ret = false;
    panel_handle_t handle = s_panel_handle_list;

    while (NULL != handle)
    {
        if (strcmp(handle->driver_name, driver_name) == 0) {
            /* found driver */
            ret = true;
            break;
        }
        handle = handle->next;
    }

    return ret;
}

static panel_handle_t _find_driver_handle(const char* find_which)
{
    panel_handle_t handle = NULL;

    for (handle = s_panel_handle_list; handle != NULL; handle = handle->next) {
        if (strcmp(handle->driver_name, find_which) == 0) {
            break;
        }
    }

    return handle;
}