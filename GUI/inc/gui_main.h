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
#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <pc_uart.h>
#include <pc_bluetooth.h>

/**
* Defines
*/
#define DEBUG 1
#define MEMS_ADDRESS 0x30 // 0b0011000 with added default 0
#define MEMS_CTRL_REG1 0x20
#define MEMS_CTRL_REG3 0x22
#define MEMS_STATUS_REG2 0x27
#define MEMS_OUT_X_L 0x28
#define MEMS_OUT_X_H 0x29
#define MEMS_OUT_Y_L 0x2A
#define MEMS_OUT_Y_H 0x2B
#define MEMS_OUT_XY_FULL_READ 0xA8

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500


/**
* Prototypes
*/
// start screen
void start_screen_init(gpointer data);
void start_screen_visible(gpointer data);

// gopro stream
void stream_screen_init(gpointer data);
void stream_screen_visible(GtkWidget *wid, gpointer data);

// data visualisation
void datavis_screen_init(gpointer data);
void datavis_screen_visible(GtkWidget *wid, gpointer data);

// menu
void menu_visible (gpointer data);
void menu_init(gpointer data);
void menu_callback_end(GSimpleAction *action, GVariant *parameter,
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

// data visualisation screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
} datavis_widgets;

// gopro stream screen
typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
} stream_widgets;

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
	start_widgets start;
	stream_widgets stream;
	datavis_widgets datavis;
	menu_widgets menu;
} widgets;

#endif /* GUI_MAIN_H */
