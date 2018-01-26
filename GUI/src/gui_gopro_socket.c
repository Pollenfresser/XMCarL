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

// Needed to open URL to start / stop GOPRO stream
#include <curl/curl.h>
CURL *curl_easy_init();
// something is not working with following line - syntax error??
//CURLcode curl_easy_setopt(CURL *handle, CURLOPT_ERRORBUFFER, char *buf);

#include <stdlib.h>

#define GOPRO_KEEP_ALIVE_PERIOD 2500
#define GOPRO_KEEP_ALIVE_CMD 2
#define GOPRO_UDP_PORT 8554

// sudo dnf install libcurl-devel

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void gopro_create_sockets();
void gopro_activate(int set_active);

// keep alive: GPHD:0:0:2:0.000000
void gopro_clean(gpointer data) {
	gopro_activate(0);
}

void gopro_init(gpointer data) {
	g_print("GOPRO init\n");
	//gopro_activate(1); // auskommentieren, wenn testen - außer gopro ist verbunden
	gopro_create_sockets();
}

// working if gopro is connected
// it's working fine, if no internet access
// need this line in makefile: CFLAGS  += `curl-config --cflags --libs`
// https://curl.haxx.se/libcurl/c/curl_easy_init.html
// https://curl.haxx.se/libcurl/c/CURLOPT_ERRORBUFFER.html
void gopro_activate(int set_active) {
	g_print("GOPRO set start / stop\n");
	CURL *curl = curl_easy_init();
	if (curl) {
		CURLcode res;
		char errbuf[CURL_ERROR_SIZE];

		if (set_active) {
			curl_easy_setopt(curl, CURLOPT_URL,
					"http://10.5.5.9/gp/gpControl/execute?p1=gpStream&a1=proto_v2&c1=restart");
			g_print("GOPRO stream gets activated\n");
		} else {
			curl_easy_setopt(curl, CURLOPT_URL,
					"http://10.5.5.9/gp/gpControl/execute?p1=gpStream&a1=proto_v2&c1=stop");
			g_print("GOPRO stream gets deactivated\n");
		}
		//curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
		errbuf[0] = 0;
		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			size_t len = strlen(errbuf);
			fprintf(stderr, "libcurl: (%d) ", res);
			if (len)
				fprintf(stderr, "%s%s", errbuf,
						((errbuf[len - 1] != '\n') ? "\n" : ""));
			else
				fprintf(stderr, "%s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
}

void gopro_create_sockets() {

}

void gopro_stream_routine(gpointer data) {
	/*while (1) {

	 }*/
}
