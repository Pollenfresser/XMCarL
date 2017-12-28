/**
 * Project: XMCarL
 *
 *  Description:
 *    - XMC as Remote Control:
 *      The first XMC is connected to an accelerometer sensor via I2C, reads the data
 *      from it and forwards it to our GUI on a PC via UART.
 *
 *    - PC - GUI:
 *      The PC is used to graphically display the current position of the sensor
 *      and display a video feed of the GoPro Hero5 mounted on a RC car.
 *      Furthermore it is connected to both XMC's to act as a
 *      transmission pipeline.
 *
 *    - XMC on Car:
 *      The XMC is directly connected directly to the controls of the RC car and via
 *      bluetooth to the PC. The forwarded data from the PC is used to control
 *      the car.
 *
 * Author: Christina Bornberg, Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: This is the main function of the XMC as Remote Control.
 * We use a mems sensor which is connected by I2C to the XMC.
 *
 * Status: Doing I2C (Chrisy)
 *
 */


/**
 * Included Files
 */
#include <main.h>
#include <debug_lib.h>
#include <remote_uart_lib.h> // will be needed for GUI
#include <remote_i2c_lib.h>

/**
 * Defines
 */

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define RX_BUFFER_SIZE 64 // UART

/**
 * Global variables
 */


/******************************************************************************
 * Start of user functions
 *****************************************************************************/


void SysTick_Handler (void)
{

}


int main (void)
{

	remote_i2c_to_mems_init();
	remote_uart_to_pc_init();
	remote_mems_init();

	while (1) {
		if(Data_Ready)
		{
			remote_i2c_write_read(MEMS_ADDRESS, memory_address, data, 1, 4);
		}
		#if DEBUG
			printf("");
		#endif

	}
}

/* EOF */
