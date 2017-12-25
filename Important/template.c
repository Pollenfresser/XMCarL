/**
 * Project: XMCarL
 *
 *  Description: // just in main files
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
 * File description:
 *
 * Status:
 */


// hier ist platz für die .h datei, globals, defines, ... in header

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

