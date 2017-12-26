#include <gui_main.h>


void activate(GtkApplication *app, gpointer data)
{
  widets *a = (widgets *) data;

  gtk_css_provier_load_from_resource (GTK_CSS_PROVIDER(a->css_style), "/gui_res/css/style.css");

  a->window = gtk_application_window_new (a->app);
  gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION(a->app));
  gtl_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (a->window), 800, 500);

  a->main_box = gtk_box_new (GKT_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (a->window), a->main_box);
  a->sub_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(a->main_box), a->sub_box, FALSE, FALSE, 0);

  // start_screen((gpointer) a);

  apply_css (a->window, a->css_style);

  gtk_widget_show (a->window);
  gtk_widget_show (a->main_box);
  gtk_widget_show (a->sub_box);

  // next_screen_1_start((gpointer) a);

}



int main (int argv, char ** argc)
{
  int status;

  // Struct which contains all of the data
  widgets *a = g_malloc(sizeof(widgets));


  a->app = gtk_application_new("org.gtk.gui", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(a->app, "activate", G_CALLBACK (activate), (gpointer) a);
  status = g_application_run (G_APPLICATION (a->app), argc, argv);

  g_object_unref (a->app);

  g_free (a);

  return status;
}
