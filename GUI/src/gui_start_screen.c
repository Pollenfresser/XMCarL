#include <gui_main.h>

void next_screen_1_start (gpointer data)
{
  widgets *a = (widgets *) data;

  gtk_widget_show_all(a->start_layout);
}
