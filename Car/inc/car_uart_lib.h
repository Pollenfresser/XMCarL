/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the header file of the XMC as Car Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status:
 *
 */

#ifndef _CAR_UART_LIB_
#define _CAR_UART_LIB_

/**
 * Included Files
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <main.h>
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
//#define BUFFER_SIZE_RX 64
#define STRING_LF 10
#define STRING_CR 13

#define ERR_OUT_OF_MEMORY 100

/**
 * Global variables
 */
extern _Bool str_available;
extern char rx_buffer[];

extern XMC_GPIO_CONFIG_t uart_tx;
extern XMC_GPIO_CONFIG_t uart_rx;
extern XMC_UART_CH_CONFIG_t uart_config;

/**
 * Prototypes
 */
 void car_uart_to_pc_init(void);
 uint8_t car_uart_send_char(char c);
 uint8_t car_uart_printf(char *fmt, ...); // TODO i have no idea
 uint8_t car_uart_send_string(char *str);
 uint8_t car_uart_get_string (char *str);


#endif /* _CAR_UART_LIB_ */

/* EOF */
