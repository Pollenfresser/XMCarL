#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

void next_screen_1_start (gpointer data);
void start_stream(GtkWidget *wid, gpointer data);




typedef struct {
  GtkApplication *app;
  GtkWidget *window;
  GtkWidget *main_box;
  GtkWidget *sub_box;
  GtkWidget *start_layout;
  GtkWidget *start_button;
  GtkWidget *start_input_entry;
  GtkStyleProvider *css_style;
} widgets;

#endif /* GUI_MAIN_H */
