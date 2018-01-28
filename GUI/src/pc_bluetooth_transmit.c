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
 * update, we are using rfcomm (5.jan)
 *
 *
 * Chrisy modified code by: "BlueZ example code to build an rfcomm client.
 This code just creates a socket and connects
 to a remote bluetooth device and sends a string.
 Programmed by Bastian Ballmann
 http://www.geektown.de"
 * Status:
 * - able to search for bluetooth devices
 * - able to send data to bluetooth module! - 5. jan
 * - should be tested!!! - 24. jan (socket will not be closed after sending)
 *
 */

#include <gui_main.h>

#include <stdio.h>
#include <string.h>

// TODO : doppelte header

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

/*
 * working - the function looks out for available bluetooth devices
 *
 * Device adress of bluetooth module on car:
 * 00:1B:35:88:0C:81
 * Handling Bluetooth device addresses
 */
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

	num_rsp = hci_inquiry(dev_id, len, MAX_BLUETOOTH_RESPONSES, NULL, &ii,
			flags);
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

void blue_clean(gpointer data) {
	widgets *a = (widgets *) data;
	close(a->sock);
}

// Sends message to the socket from blue_comm_init
gboolean blue_send_data(gpointer data) {
	widgets *a = (widgets *) data;
	sprintf(a->bluetooth->message, "%ld,%ld\n", received.steering, received.throttle); // TODO: received in uart / 2000 !?
	puts(a->bluetooth->message);
	printf("Sending data %s\n", a->bluetooth->message);
	send(a->sock, a->bluetooth->message, strlen(a->bluetooth->message), 0); // TODO initialize message
	// printf("Disconnect.\n");
	// close(a->sock);
	return TRUE;
}

int blue_comm_init(gpointer data) {
	widgets *a = (widgets *) data;

	struct sockaddr_rc local_addr, remote_addr;
	struct hci_dev_info device_info;

	// info of own device (laptop)
	if (hci_devinfo(0, &device_info) < 0) {
		perror("HCI device info failed");
		exit(1);
	}

	printf("Local device %s\n", batostr(&device_info.bdaddr));

	local_addr.rc_family = AF_BLUETOOTH;
	local_addr.rc_bdaddr = device_info.bdaddr;
	local_addr.rc_channel = 0;

	remote_addr.rc_family = AF_BLUETOOTH;
	str2ba(a->bluetooth[a->choosen_blue_dev].addr, &remote_addr.rc_bdaddr);
	remote_addr.rc_channel = 1;

	if ((a->sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
		perror("socket"); // go back to start devices
		start_screen_visible((gpointer) a);
	}

	if (bind(a->sock, (struct sockaddr *) &local_addr, sizeof(local_addr))
			< 0) {
		perror("bind"); // go back to start devices
		start_screen_visible((gpointer) a);
	}

	printf("Remote device %s\n", a->bluetooth[a->choosen_blue_dev].addr);

	if (connect(a->sock, (struct sockaddr *) &remote_addr, sizeof(remote_addr))
			< 0) {
		perror("connect"); // go back to start devices
		start_screen_visible((gpointer) a);
	}

	return 0;
}
