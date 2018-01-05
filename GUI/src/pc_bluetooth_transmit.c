/**
 * Project: XMCarL
 *
 * Author: Chrisy
 * Modified:
 * Used code: https://people.csail.mit.edu/albert/bluez-intro/c404.html
 *
 * Date of creation: 27.12.2017
 *
 * File description: Bluetooth connection on the pc side
 * data from uart will be forwarded to the car
 *
 * using bluez with c
 * not working becaude heder - compile it with:  gcc -o simplescan simplescan.c -lbluetooth
 *
 * Status:
 * - able to search for bluetooth devices
 *
 *
 */


#include <gui_main.h>

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// working - the function looks out for available
// bluetooth devices
int blue_search_for_available_devices(gpointer data) {
	widgets *a = (widgets *) data;

	inquiry_info *ii = NULL;
	int num_rsp;
	int dev_id, sock, len, flags;
	int i;
	char addr[19] = { 0 };
	char name[248] = { 0 };

	dev_id = hci_get_route(NULL);
	sock = hci_open_dev(dev_id);
	if (dev_id < 0 || sock < 0) {
		perror("opening socket");
		exit(1);
	}

	len = 8;
	flags = IREQ_CACHE_FLUSH;
	ii = (inquiry_info*) malloc(MAX_BLUETOOTH_RESPONSES * sizeof(inquiry_info));

	num_rsp = hci_inquiry(dev_id, len, MAX_BLUETOOTH_RESPONSES, NULL, &ii, flags);
	if (num_rsp < 0)
		perror("hci_inquiry");

	for (i = 0; i < num_rsp; i++) {
		ba2str(&(ii + i)->bdaddr, addr);
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(sock, &(ii + i)->bdaddr, sizeof(name), name, 0)
				< 0)
			strcpy(name, "[unknown]");

		strcpy(a->bluetooth[i].name, name);
		strcpy(a->bluetooth[i].addr, addr);

		printf("%s  %s\n", addr, name);
	}

	free(ii);
	close(sock);
	return num_rsp;
}

/*
 * Device adress of bluetooth module on car:
 * 00:1B:35:88:0C:81
 */

void blue_choose_device_to_communicate(){





}

void bluetooth_client(void)
{
    struct sockaddr_l2 addr = { 0 };
    int s, status;
    char *message = "hello!";
    char dest[18] = "00:1B:35:88:0C:81";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

    // set the connection parameters (who to connect to)
    addr.l2_family = AF_BLUETOOTH;
    addr.l2_psm = htobs(0x1001);
    str2ba( dest, &addr.l2_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    if( status == 0 ) {
        status = write(s, "hello!", 6);
    }

    if( status < 0 ) perror("uh oh");

    close(s);
}


/*
 * determine which transport protocol to use
 * RFCOMM + TCP or
 * L2CAP + UDP - never retransmit (logical link control and adaptation protocol)
 */
 void blue_how_to_communicate(){

 }

/*
 * Ports available in L2CAP: 4097 - 32765 (odd) - dynamic ports
 *
 * The host machine operates a server application, called the
 * SDP server, that uses one of the few L2CAP reserved port numbers.
 *
 * Bluetooth is to assign a 128-bit number, called the Universally Unique Identifier (UUID), at design time
 *
 */


void blue_outgoing_connection(){

}

void blue_accept_ingoing_connection(){

}

void blue_send_data(){

    }

void blue_receive_data(){

}


