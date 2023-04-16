/*
 * Copyright (C) 2022 MESCO Engineering GmbH
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_mesco-com-mcu1
 * @{
 *
 * @file
 * @brief       Board specific definitions for the MESCO_COM_MCU1 board
 *
 * @author      Onur Demir <onur.demir@mesco.de>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    ztimer configuration values
 * @{
 */
#define CONFIG_ZTIMER_USEC_ADJUST_SET     (2)
#define CONFIG_ZTIMER_USEC_ADJUST_SLEEP   (3)
/** @} */


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
