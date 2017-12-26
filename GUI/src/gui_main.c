#include <gui_main.h>


int main (int argv, char ** argc)
{
  int status;

  widgets *a = g_malloc(sizeof(widgets));

  a->app = gtk_application_new("org.gtk.gui", G_APPLICATION_FLAGS_NONE);

  return 0;
}
