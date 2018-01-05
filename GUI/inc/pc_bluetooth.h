/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified:
 *
 * Date of creation: 30.12.2017
 *
 * File description: Bluetooth connection
 *
 * Status: I have no idea what i'm doing :(
 */



#ifndef PC_BLUETOOTH_H
#define PC_BLUETOOTH_H

/**
* Included Files
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

/**
* Defines
*/
#define DEBUG 1
#define MAX_BLUETOOTH_RESPONSES 255
/**
 * Pins
 */

/**
* Prototypes
*/

int blue_search_for_available_devices(gpointer data);
void wait_create_button_for_each_device(int count_devices, gpointer data);
void bluetooth_client(void);

/**
* Global variables
*/



#endif // PC_BLUETOOTH_H


/* EOF */
