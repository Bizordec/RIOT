/*
 * Copyright (C) 2017-2018 Unwired Devices [info@unwds.com]
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
 * @file		ls-init-device.h
 * @brief       LoRa module settings
 * @author      Oleg Artamonov
 */
#ifndef LS_INIT_DEVICE_H_
#define LS_INIT_DEVICE_H_

#include "shell.h"
#include "net/netdev.h"
#include "ls-mac-types.h"

extern void init_normal(shell_command_t *commands);

void init_role(shell_command_t *shell_commands);

void ls_setup_sx127x(netdev_t *dev, ls_datarate_t dr, uint32_t frequency);

#endif /* LS_INIT_DEVICE_H_ */
