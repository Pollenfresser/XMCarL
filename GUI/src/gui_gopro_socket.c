/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified:
 *
 * Date of creation: 24.01.2018
 *
 * File description: Sockets to communicate with the gopro
 * I used this python file: https://github.com/KonradIT/GoProStream/blob/master/GoProStream.py
 *
 * Status: at the beginning
 *
 */

// /live/amba.m3u8
#include <gui_main.h>

#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <curl/curl.h>

#include <stdlib.h>

// sudo dnf install libcurl-devel

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void gopro_create_sockets();

// keep alive: GPHD:0:0:2:0.000000
void gopro_clean(gpointer data) {

}

void gopro_init(gpointer data) {
	int keep_alive_period = 2500;
	int keep_alive_cmd = 2;
	int udp_port = 8554;

	gopro_create_sockets();
}

void gopro_create_sockets() {

//	url_fopen("http://10.5.5.9/gp/gpControl/execute?p1=gpStream&a1=proto_v2&c1=restart", "r");

}

void gopro_stream_routine(gpointer data) {
	while (1) {

	}
}
