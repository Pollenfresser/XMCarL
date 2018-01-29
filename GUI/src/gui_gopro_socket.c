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
 * Status: you can send keep alive message to gopro and open url with curl to
 * start gopro stream (just can't read the stream :(
 *
 * http://www.willemer.de/informatik/unix/unprsock.htm
 * socket 	Anforderung eines Kommunikationsendpunktes
 * bind 	Lege die Portnummer fest
 * -listen 	Festlegen der Pufferzahl für Anfragen
 * -accept 	Auf Anfragen warten
 * connect 	Verbindung anfordern
 * send 	Senden von Daten
 * -recv 	Empfangen von Daten
 * close 	Schließen des Sockets
 *
 */

// /live/amba.m3u8
#include <gui_main.h>

// Needed to open URL to start / stop GOPRO stream
#include <curl/curl.h>
CURL *curl_easy_init();

// sudo dnf install libcurl-devel

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void gopro_create_sockets(gpointer data);
int gopro_activate(int set_active);
gboolean gopro_stream_routine(gpointer data);
gpointer goproThread(gpointer data);


// keep alive: GPHD:0:0:2:0.000000
void gopro_clean(gpointer data) {
	widgets *a = (widgets *) data;
	gopro_activate(0);
	close(a->gopro.sock);
	// close socket
	// freeaddrinfo(addr_info....
}

void gopro_init(gpointer data) {
	g_print("GOPRO init\n");
	widgets *a = (widgets *) data;
	if(gopro_activate(1)){
		gopro_create_sockets((gpointer) a);
	}
}

// working
// there is a problem with closing (timeout)
// need this line in makefile: CFLAGS  += `curl-config --cflags --libs`
// https://curl.haxx.se/libcurl/c/curl_easy_init.html
// https://curl.haxx.se/libcurl/c/CURLOPT_ERRORBUFFER.html
int gopro_activate(int set_active) {
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
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
		errbuf[0] = 0;
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			if (res == CURLE_OPERATION_TIMEDOUT){
				g_print("GoPro might not be connected\n");
			}
			size_t len = strlen(errbuf);
			fprintf(stderr, "libcurl: (%d) ", res);
			if (len)
				fprintf(stderr, "%s%s", errbuf,
						((errbuf[len - 1] != '\n') ? "\n" : ""));
			else
				fprintf(stderr, "%s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			return 0;
		}else{
			curl_easy_cleanup(curl);
			return 1;
		}
	}
	return 0;
}

void gopro_create_sockets(gpointer data) {

	widgets *a = (widgets *) data;
	GThread* gthread_gopro;
	int res;
	int sock;

	struct addrinfo hints_client, *addr_info_client; // for connect
	memset(&hints_client, 0, sizeof hints_client);
	hints_client.ai_family = AF_INET;
	// SOCK_DGRAM => Connectionless, unreliable datagrams
	// of fixed maximum length.
	hints_client.ai_socktype = SOCK_DGRAM;
	res = getaddrinfo("10.5.5.9", "8554", &hints_client, &addr_info_client);

	a->gopro.sock = socket(addr_info_client->ai_family, addr_info_client->ai_socktype, addr_info_client->ai_protocol);

	if(a->gopro.sock < 0){
		g_print("Error: socket\n");
	}else{
		g_print("Socket for GoPro is created\n");
	}

	if( connect(a->gopro.sock, addr_info_client->ai_addr, addr_info_client->ai_addrlen) < 0){
		g_print("Error: connect\n");
	}else{
		g_print("GoPro is connected\n");
		gthread_gopro = g_thread_new("data_transfer", (GThreadFunc) goproThread, (gpointer)a);
		g_thread_join (gthread_gopro);
	}
}

/*
 * all 2.5 seconds, the gopro needs a new keep alive message
 */
gpointer goproThread(gpointer data){
  widgets *a = (widgets *) data;
  g_print("routine gopro\n");
  g_timeout_add(2500, (GSourceFunc) gopro_stream_routine, (gpointer) a);
  return NULL;

}

gboolean gopro_stream_routine(gpointer data) {

	widgets *a = (widgets *) data;
	send(a->gopro.sock, "_GPHD_:0:0:2:0.000000", 21, 0);

	return TRUE;
}
