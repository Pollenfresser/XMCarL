#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>


typedef struct {
  GtkApplication *app;
  GtkWidget *window;
  GtkWidget *main_box;
  GtkWidget *sub_box;
  GtkStyleProvider *css_style;
} widgets;

#endif /* GUI_MAIN_H */
