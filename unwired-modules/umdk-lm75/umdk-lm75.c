/*
 * Copyright (C) 2016 Unwired Devices [info@unwds.com]
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup
 * @ingroup
 * @brief
 * @{
 * @file		umdk-lm75.c
 * @brief       umdk-lm75 module implementation
 * @author      Eugene Ponomarev
 */

#ifdef __cplusplus
extern "C" {
#endif

/* define is autogenerated, do not change */
#undef _UMDK_MID_
#define _UMDK_MID_ UNWDS_LM75_MODULE_ID

/* define is autogenerated, do not change */
#undef _UMDK_NAME_
#define _UMDK_NAME_ "lm75"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "periph/gpio.h"

#include "board.h"

#include "unwds-common.h"
#include "umdk-lm75.h"

#include "thread.h"
#include "xtimer.h"

#include "lm75.h"

static uwnds_cb_t *callback;

static lm75_t lm75;

int umdk_lm75_shell_cmd(int argc, char **argv) {
    if (argc == 1) {
        puts ("[umdk-" _UMDK_NAME_ "] get - get results now");
        return 0;
    }
    
    char *cmd = argv[1];
	
    if (strcmp(cmd, "get") == 0) {
        int temp = lm75_get_ambient_temperature(&lm75);
        
        char buf[10];
        int_to_float_str(buf, temp, 3);
        printf("[umdk-" _UMDK_NAME_ "] Temperature: %s C\n", buf);
    }
    
    return 1;
}

void umdk_lm75_init(uint32_t *non_gpio_pin_map, uwnds_cb_t *event_callback)
{
    (void) non_gpio_pin_map;

    callback = event_callback;

    lm75.params.i2c = UMDK_LM75_I2C;
    lm75.params.a1 = 0;
    lm75.params.a2 = 0;
    lm75.params.a3 = 0;

    if (lm75_init(&lm75)) {
        puts("[umdk-" _UMDK_NAME_ "] Error initializing LM75 sensor");
        return;
    }
    
    unwds_add_shell_command(_UMDK_NAME_, "type '" _UMDK_NAME_ "' for commands list", umdk_lm75_shell_cmd);
}

bool umdk_lm75_cmd(module_data_t *data, module_data_t *reply)
{
	if (data->length < 1)
		return false;

	umdk_lm75_cmd_t c = data->data[0];

	switch (c) {
	case UMDK_LM75_CMD_POLL:
	{
		int temp = lm75_get_ambient_temperature(&lm75);
		int16_t data = (temp/100);
		
		reply->length = 1 + sizeof(data);
		reply->data[0] = _UMDK_MID_;
		memcpy(reply->data + 1, &data, sizeof(data));
		break;
	}
	default:
		break;
	}

    return true;
}

#ifdef __cplusplus
}
#endif
