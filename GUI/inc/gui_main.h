#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>


typedef struct {
GtkWidget *layout;
  GtkWidget *button;
  
  	GtkWidget *label_name;
	GtkWidget *img;

} start_widgets;

typedef struct {
GtkWidget *layout;
  GtkWidget *button;
  
  	GtkWidget *label_name;
	GtkWidget *img;

} datavis_widgets;

typedef struct {
GtkWidget *layout;
  GtkWidget *button;
GtkWidget *video_area;
  
  	GtkWidget *label_name;
	GtkWidget *img;

} stream_widgets;

typedef struct {
  GtkApplication *app;
  GtkWidget *window;
  GtkWidget *main_box;
  GtkStyleProvider *css_style;
	start_widgets start;
stream_widgets stream;
datavis_widgets datavis;
} widgets;


void start_screen_init (gpointer data);
void start_screen_visible (gpointer data);

void stream_screen_init(gpointer data);
void stream_screen_visible(GtkWidget *wid, gpointer data);

void datavis_screen_init(gpointer data);
void datavis_screen_visible(GtkWidget *wid, gpointer data);



#endif /* GUI_MAIN_H */
