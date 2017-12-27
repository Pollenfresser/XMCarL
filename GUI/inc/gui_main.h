#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

typedef struct {
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *img;
} start_widgets;

typedef struct {
	GtkWidget *layout;
	GtkWidget *label;
} datavis_widgets;

typedef struct {
	GtkWidget *layout;
	GtkWidget *label;

} stream_widgets;

typedef struct {
	GtkWidget *menubar;

} menu_widgets;

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

#endif /* GUI_MAIN_H */
