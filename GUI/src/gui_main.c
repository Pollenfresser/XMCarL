#include <gui_main.h>


void apply_css(GtkWidget *widget, GtkStyleProvider *css_s)
{
  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), css_s, G_MAXUINT);

  if(GTK_IS_CONTAINER (widget))
  {
    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, css_s);
  }
}


void start_screen (gpointer data)
{
  widgets *a = (widgets *) data;
  gint get_hight, get_width;
  GtkWidget *label_name;
	GtkWidget *img;

  a->start_layout = gtk_fixed_new();

  label_name = gtk_label_new ("Welcome to XMCarL");

	img = gtk_image_new_from_file ("img/xmcarl.png");
gtk_widget_show_all(img);


  a->start_button = gtk_button_new_with_label("Start Car");
  gtk_widget_set_size_request(a->start_button, 300, 100);
  g_signal_connect(a->start_button, "clicked", G_CALLBACK(start_stream), (gpointer) a);


  gtk_box_pack_start (GTK_BOX(a->main_box), a->start_button, FALSE, FALSE, 0);	
	

  gtk_box_pack_start (GTK_BOX(a->main_box), label_name, FALSE, FALSE, 0);	
  gtk_box_pack_start (GTK_BOX(a->main_box), img, FALSE, FALSE, 0);

  gtk_box_pack_start (GTK_BOX(a->main_box), a->start_layout, FALSE, FALSE, 0);

gtk_widget_show_all(a->main_box);
}


void activate(GtkApplication *app, gpointer data)
{
  widgets *a = (widgets *) data;

  a->css_style = GTK_STYLE_PROVIDER (gtk_css_provider_new());
 // gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER(a->css_style), "/gui_res/css/style.css");

  a->window = gtk_application_window_new (a->app);
  gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION(a->app));
  gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (a->window), 800, 500);

  a->main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (a->window), a->main_box);
  a->sub_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX(a->main_box), a->sub_box, FALSE, FALSE, 0);

  start_screen((gpointer) a);

 // apply_css (a->window, a->css_style);

  gtk_widget_show (a->window);
  gtk_widget_show (a->main_box);
  gtk_widget_show (a->sub_box);

  next_screen_1_start((gpointer) a);

}



int main (int argc, char ** argv)
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
