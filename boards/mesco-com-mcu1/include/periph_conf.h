/*
 * Copyright (C) 2022 MESCO Engineering GmbH
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_mesco-com-mcu1
 * @{
 *
 * @file
 * @name        Peripheral MCU configuration for the MESCO_COM_MCU1 board (based on stm32f429ii-h7)
 *
 * @author      Onur Demir <onur.demir@mesco.de>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

/* This board provides an LSE */
#ifndef CONFIG_BOARD_HAS_LSE
#define CONFIG_BOARD_HAS_LSE    1
#endif 

/* This board provides an HSE */
#ifndef CONFIG_BOARD_HAS_HSE
#define CONFIG_BOARD_HAS_HSE    1
#endif

/* The HSE provides a 26MHz clock 
 * to get 180MHz -> ((CLOCK_HSE / CONFIG_CLOCK_PLL_M) *  CONFIG_CLOCK_PLL_N) / CONFIG_CLOCK_PLL_P
 */
#define CLOCK_HSE               MHZ(26)
#define CONFIG_CLOCK_PLL_M      (13)
#define CONFIG_CLOCK_PLL_N      (180)
#define CONFIG_CLOCK_PLL_P      (2)


#include "periph_cpu.h"
#include "clk_conf.h"
#include "cfg_timer_tim5.h"
#include "mii.h"

/* for usart6 we use the interrupt service routine provided by MESCO Engineering */
#include "HALPkg/InterfacePkg/UARTPkg/UART.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    DMA streams configuration
 * @{
 */
static const dma_conf_t dma_config[] = {
    { .stream = 14 },  /* DMA2 Stream 6 - USART6_TX */
    { .stream = 8 },    /* DMA2 Stream 0 - ETH_TX  */
};

#define DMA_0_ISR           isr_dma2_stream6    /* USART6 - MESCO ServiceCom */
#define DMA_1_ISR           isr_dma2_stream0    /* ETH*/

#define DMA_NUMOF           ARRAY_SIZE(dma_config)
/** @} */


/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev        = UART5,
        .rcc_mask   = RCC_APB1ENR_UART5EN,
        .rx_pin     = GPIO_PIN(PORT_D, 2),
        .tx_pin     = GPIO_PIN(PORT_C, 12),
        .rx_af      = GPIO_AF8,
        .tx_af      = GPIO_AF8,
        .bus        = APB1,
        .irqn       = UART5_IRQn,      
    },
    {
        .dev        = USART6,
        .rcc_mask   = RCC_APB2ENR_USART6EN,
        .rx_pin     = GPIO_PIN(PORT_C, 7),
        .tx_pin     = GPIO_PIN(PORT_C, 6),
        .rx_af      = GPIO_AF8,
        .tx_af      = GPIO_AF8,
        .bus        = APB2,
        .irqn       = USART6_IRQn,
#ifdef MODULE_PERIPH_DMA
        .dma        = 0,
        .dma_chan   = 5,
#endif
    }
};

#define UART_0_ISR              (isr_uart5)
//#define UART_1_ISR              (isr_usart6)
#define MESCO_UART_IrqHandler    (isr_usart6)

#define UART_NUMOF          ARRAY_SIZE(uart_config)
/** @} */


/**
 * @name ETH configuration
 * @{
 */
static const eth_conf_t eth_config = {
    .mode = RMII,
    .speed = MII_BMCR_SPEED_100 | MII_BMCR_FULL_DPLX,
    .dma = 1,
    .dma_chan = 8,
    .phy_addr = 0x00,
    .pins = {
        GPIO_PIN(PORT_G, 13),   /* TXD0    */
        GPIO_PIN(PORT_G, 14),   /* TXD1    */
        GPIO_PIN(PORT_G, 11),   /* TX_EN   */
        GPIO_PIN(PORT_C, 4),    /* RXD0    */
        GPIO_PIN(PORT_C, 5),    /* RXD1    */
        GPIO_PIN(PORT_A, 7),    /* CRS_DV  */
        GPIO_PIN(PORT_C, 1),    /* MDC     */
        GPIO_PIN(PORT_A, 2),    /* MDIO    */
        GPIO_PIN(PORT_A, 1),    /* REF_CLK */
    }
};

#define ETH_DMA_ISR        isr_dma2_stream0
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
