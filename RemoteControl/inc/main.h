/**
 * Project: XMCarL
 *
 * Author:
 * Modified: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the I2C header file of the XMC as Remote Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status: Done I2C (Chrisy)
 * Lucas Review
 */


#ifndef MAIN_H
#define MAIN_H

/**
* Included Files
*/

#include <stdio.h>
#include <stdlib.h>
#include <xmc_gpio.h>
// User files
#include <debug_lib.h>
#include <remote_uart_lib.h> // will be needed for GUI
#include <remote_i2c_lib.h>
#include <remote_mems.h>

/**
* Defines
*/
#define DEBUG 1
#define DEBUG_ALL 0
#define I2C 1
#define UART 1

#define MEMS_ADDRESS 0x30 // 0b0011000 with added default 0
#define MEMS_CTRL_REG1 0x20
#define MEMS_CTRL_REG3 0x22
#define MEMS_CTRL_REG4 0x23
#define MEMS_STATUS_REG2 0x27
#define MEMS_OUT_X_L 0x28
#define MEMS_OUT_X_H 0x29
#define MEMS_OUT_Y_L 0x2A
#define MEMS_OUT_Y_H 0x2B
#define MEMS_OUT_XY_FULL_READ 0xA8
#define ONE_HZ_X_AND_Y 0b00010011
#define TEN_HZ_X_AND_Y 0b00100011
#define ZWENTYFIFE_HZ_X_AND_Y 0b00110011

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500


/**
 * Pins
 */
#define DATAREADY P0_3
#define LED1 P1_1
#define LED2 P1_0


/**
* Prototypes
*/


/**
* Global variables
*/



#endif // MAIN_H


/* EOF */
