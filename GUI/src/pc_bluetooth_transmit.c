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
 * - able to send data to bluetooth module! - 5 jan
 *
 *
 */

#include <gui_main.h>

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdlib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>

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

/*
 * Device adress of bluetooth module on car:
 * 00:1B:35:88:0C:81
 * Handling Bluetooth device addresses
 */

void blue_choose_device_to_communicate() {

}

/*
 * determine which transport protocol to use
 * RFCOMM + TCP or
 * L2CAP + UDP - never retransmit (logical link control and adaptation protocol)
 */

/*
 BlueZ example code to build an rfcomm client.
 This code just creates a socket and connects
 to a remote bluetooth device and sends a string.
 Programmed by Bastian Ballmann
 http://www.geektown.de
 Compile with gcc -lbluetooth <executable> <source>
 */

void blue_get_own_device_info() {

}

void blue_bind_and_connect() {

}

void blue_send_data(int sock, gpointer data) {
	widgets *a = (widgets *) data;

	printf("Sending data %s\n", a->bluetooth->message);
	send(sock, a->bluetooth->message, strlen(a->bluetooth->message), 0); // TODO initialize message
	printf("Disconnect.\n");
	close(sock);

}

int blue_communication(gpointer data) {
	widgets *a = (widgets *) data;

	int sock;
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

	if ((sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
		perror("socket"); // go back to start devices
	}

	if (bind(sock, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
		perror("bind"); // go back to start devices
		exit(1);
	}

	printf("Remote device %s\n", a->bluetooth[a->choosen_blue_dev].addr);

	if (connect(sock, (struct sockaddr *) &remote_addr, sizeof(remote_addr))
			< 0) {
		perror("connect");
		exit(1); // go back to start devices
	}

	blue_send_data(sock, (gpointer)a);
	return 0;
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

/*  this code is working!!!!
 int sock, d;
 struct sockaddr_rc laddr, raddr;
 struct hci_dev_info di;

 if(hci_devinfo(0, &di) < 0)
 {
 perror("HCI device info failed");
 exit(1);
 }

 printf("Local device %s\n", batostr(&di.bdaddr));

 laddr.rc_family = AF_BLUETOOTH;
 laddr.rc_bdaddr = di.bdaddr;
 laddr.rc_channel = 0;

 raddr.rc_family = AF_BLUETOOTH;
 str2ba("00:1B:35:88:0C:81",&raddr.rc_bdaddr);
 raddr.rc_channel = 1;

 if( (sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0)
 {
 perror("socket");
 }

 if(bind(sock, (struct sockaddr *)&laddr, sizeof(laddr)) < 0)
 {
 perror("bind");
 exit(1);
 }

 printf("Remote device %s\n", "00:1B:35:88:0C:81");

 if(connect(sock, (struct sockaddr *)&raddr, sizeof(raddr)) < 0)
 {
 perror("connect");
 exit(1);
 }

 printf("Connected.\nSending data %s\n","hey");
 send(sock,"hey",strlen("hey"),0);
 printf("Disconnect.\n");
 close(sock);
 return 0;
 */

