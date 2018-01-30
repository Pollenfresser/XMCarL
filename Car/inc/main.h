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

#ifndef MAIN
#define MAIN

/**
 * Included Files
 */


#include <stdio.h>
#include <stdlib.h>
#include <xmc_gpio.h>
// User files
#include <debug_lib.h>
#include <car_pwm_lib.h>
#include <car_uart_lib.h>


/**
 * Defines
 */
#define RX_BUFFER_SIZE 64

#define UART_EN 1
#define PWM_EN  1

#define DEBUG 0

/**
 * Pins
 */
#define LED1 P1_1

/**
 * Global variables
 */

/**
 * Prototypes
 */


#endif /* MAIN */

/* EOF */
