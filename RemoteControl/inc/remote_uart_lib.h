/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg, Lucas Ullrich
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

_Bool str_available = false;
char rx_buffer[BUFFER_SIZE_RX] = {0};

// structures
XMC_GPIO_CONFIG_t uart_tx = {
	.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
	.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t uart_rx = {
	.mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

XMC_UART_CH_CONFIG_t uart_config = {
	.data_bits = 8U,
	.stop_bits = 1U,
	.baudrate = 115200U
};


/**
 * Prototypes
 */

void _init_uart0_ch0(void);
uint8_t _uart_send_char(char c);
uint8_t _uart_printf(char *fmt, ...); // TODO i have no idea
uint8_t _uart_send_string(char *str);
uint8_t _uart_get_string (char *str);
#endif /* REMOTE_UART_H_ */

/* EOF */
