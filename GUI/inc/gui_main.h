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

#include <gdk/gdk.h>
#if defined (GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined (GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif


#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

// own XMCarl Header
#include <pc_uart.h>
#include <pc_bluetooth.h>

// GStreamer
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <gdk/gdk.h>

/**
* Defines
*/
#define DEBUG 1
#define SENSOR_REFRESH_CYCLE 1500

#define MESSAGE_SIZE 64 // bluetooth - same as u-controller


/**
* Prototypes
*/

// connection via bluetooth from pc to car
int blue_comm_init(gpointer data);
void blue_clean(gpointer data);
gboolean blue_send_data(gpointer data);

// connection to gopro
void gopro_init(gpointer data);

// SCREENS

// start screen
void start_screen_init(gpointer data);
void start_screen_visible(gpointer data);

// wait screen
void wait_screen_init(gpointer data);
void wait_screen_visible(GtkWidget *wid, gpointer data);
void wait_screen_bluetooth(GtkWidget *wid, gpointer data);

// stream from gopro
int stream_screen_init(gpointer data);
void stream_screen_visible(GtkWidget *wid, gpointer data);
void stream_start_stream(gpointer data);
void stream_screen_clean(gpointer data);

// data visualisation
void datavis_screen_init(gpointer data);
void datavis_screen_visible(GtkWidget *wid, gpointer data);

// no matter what button is pressed, we need to get this initialised
// - bluetooth connection
// - gopro connection
void brainfuck_init(gpointer data);

// menu
void menu_visible (gpointer data);
void menu_init(gpointer data);
void menu_callback_car_connect(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_stream(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_visual(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void menu_callback_about(GSimpleAction *action, GVariant *parameter,
		gpointer data);
void destroy_dialog(GtkDialog *dialog, gint response_id, gpointer data);



/**
* Global variables
*/

// start screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *img;
} start_widgets;

// wait screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *label;
} wait_widgets;

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
	start_widgets start;
	stream_widgets stream;
	gopro_struct gopro;
	datavis_widgets datavis;
	wait_widgets wait;
	menu_widgets menu;
	bluetooth_data *bluetooth; // allocate
} widgets;

#endif /* GUI_MAIN_H */
