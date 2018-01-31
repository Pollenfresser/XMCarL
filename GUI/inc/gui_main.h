/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Help from: Lucas Ullrich
 *
 * Date of creation: 25.12.2017
 *
 * File description: Headerfile of the Graphical User Interface
 *
 * Status: done, so far, maybe need some more structs and header includes
 */
#ifndef GUI_MAIN_H
#define GUI_MAIN_H

/**
* Included Files
*/

// GUI
#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>

// own XMCarl Header
#include <pc_uart.h>
#include <pc_bluetooth.h>

// GStreamer
#include <gdk/gdk.h>
#if defined (GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined (GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

// GoPro
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <fcntl.h>

/**
* Defines
*/
#define DEBUG 0
#define SENSOR_REFRESH_CYCLE 30

#define MESSAGE_SIZE 64 // bluetooth - same as u-controller

//enum states { CONNECTED, DISCONNECTED, SEND, RECEIVE };

#define INIT 0
#define CONNECTED 1
#define DISCONNECTED 2
#define SENDING 3
#define RECEIVING 4
#define ERROR 5
#define SUCCESS 6

/**
* Prototypes
*/

// connection via bluetooth from pc to car
int blue_comm_init(gpointer data);
void blue_clean(gpointer data);
gboolean blue_send_data(gpointer data);

// uart for car connection
gpointer uartThread(gpointer data);

// connection to gopro
void gopro_init(GtkWidget *wid, gpointer data);
void gopro_clean(gpointer data);
void gopro_create_sockets(gpointer data);
int gopro_activate(int set_active, gpointer data);
gboolean gopro_stream_routine(gpointer data);
gpointer goproThread(gpointer data);

// home screen
void home_screen_init(gpointer data);
void home_screen_visible(gpointer data);

// car connect screen
void car_screen_init(gpointer data);
void car_screen_visible(GtkWidget *wid, gpointer data);
void car_bluetooth(GtkWidget *wid, gpointer data);

// stream from gopro
int stream_screen_init(gpointer data);
void stream_screen_visible(GtkWidget *wid, gpointer data);
void stream_start_stream(gpointer data);
void stream_screen_clean(gpointer data);

// data visualisation
void datavis_screen_init(gpointer data);
void datavis_screen_visible(GtkWidget *wid, gpointer data);

void status_screen_init(gpointer data);
void status_screen_visible(GtkWidget *wid, gpointer data);
void status_screen_refresh_info(GtkWidget *wid, char info[1024]);
void status_screen_refresh_status(GtkWidget *wid, int status);


// no matter what button is pressed, we need to get this initialised
// - bluetooth connection
// - gopro connection
void brainfuck_init(gpointer data);

// menu
void menu_visible (gpointer data);
void menu_init(gpointer data);

void menu_callback_home(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_car(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_stream(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_datavis(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_status(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_about(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void destroy_dialog(GtkDialog *dialog, gint response_id, gpointer data);

/**
* Global variables
*/

// home screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *button_car;
	GtkWidget *button_stream;
	GtkWidget *button_datavis;
	GtkWidget *button_status;
	GtkWidget *label;
	GtkWidget *img;
} home_widgets;

// car screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *label;
} car_widgets;

typedef struct{
	char addr[19];
	char name[248];
	char message[MESSAGE_SIZE];
} bluetooth_data;

// data visualisation screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
} datavis_widgets;

// status screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
	int gopro;
	int car;
	int remote;
	int stream;
	char gopro_info[1024];
	char car_info[1024];
	char remote_info[1024];
	char stream_info[1024];
	GtkWidget *label_gopro_status;
	GtkWidget *label_car_status;
	GtkWidget *label_remote_status;
	GtkWidget *label_stream_status;
	GtkWidget *label_gopro_info;
	GtkWidget *label_car_info;
	GtkWidget *label_remote_info;
	GtkWidget *label_stream_info;
	GtkWidget *button_gopro_connect;
	GtkWidget *button_uart_connect;
} status_widgets;


// gopro stream screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
	GtkWidget *video_window;
	GstElement *playbin;
	GstElement *source;
	GstElement *sink;
} stream_widgets;

typedef struct {
	int sock;
} gopro_struct;

// menu
typedef struct {
	GtkWidget *menubar;

} menu_widgets;

// all widgets together
typedef struct {
	GtkApplication *app;
	GtkWidget *window;
	GtkWidget *main_box;
	GtkStyleProvider *css_style;

	// Bluetooth
	int choosen_blue_dev;
	int sock;

	// Data
	home_widgets home;
	stream_widgets stream;
	gopro_struct gopro;
	datavis_widgets datavis;
	status_widgets status;
	car_widgets car;
	menu_widgets menu;
	bluetooth_data *bluetooth; // allocate
} widgets;

#endif /* GUI_MAIN_H */
