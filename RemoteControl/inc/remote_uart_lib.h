/**
 * Project: XMCarL
 *
 * Author:
 * Modified: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the UART header file of the XMC as Remote Control.
 * We use UART to communicate with the Graphical User Interface on the PC
 *
 * Status: Doing UART (Chrisy)
 *
 *
 */

#ifndef REMOTE_UART_H_
#define REMOTE_UART_H_

/**
 * Included Files
 */

#include <stdio.h>
#include <stdarg.h>
#include <xmc_uart.h>
#include <xmc_gpio.h>


/**
 * Defines
 */

#define UART_TX P1_5
#define UART_RX P1_4

#define RX_FIFO_INITIAL_LIMIT 0
#define TX_FIFO_INITIAL_LIMIT 0

#define BUFFER_SIZE_PRINTF 255
#define BUFFER_SIZE_RX 64
#define STRING_LF 10
#define STRING_CR 13

#define ERR_OUT_OF_MEMORY 100


/**
 * Global variables
 */

extern _Bool str_available;
extern char rx_buffer[BUFFER_SIZE_RX];

// structures
extern XMC_GPIO_CONFIG_t uart_tx;
extern XMC_GPIO_CONFIG_t uart_rx;
extern XMC_UART_CH_CONFIG_t uart_config;


/**
 * Prototypes
 */

void remote_uart_to_pc_init(void);
uint8_t remote_uart_send_char(char c);
uint8_t remote_uart_printf(char *fmt, ...);
uint8_t remote_uart_send_string(char *str);
uint8_t remote_uart_get_string (char *str);
#endif /* REMOTE_UART_H_ */

/* EOF */
