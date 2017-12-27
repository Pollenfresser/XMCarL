#include <gui_main.h>

void stream_screen_visible(GtkWidget *wid, gpointer data)
{
	widgets *a = (widgets *) data;
  	gtk_widget_show_all(a->stream.layout);

  	gtk_widget_set_visible(a->start.layout, FALSE);
  	gtk_widget_set_visible(a->datavis.layout, FALSE);


}

void stream_screen_init(gpointer data)
{
    widgets *a = (widgets *) data;

a->stream.layout = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
/*
a->stream.video_area = gtk_drawing_area_new();
 gtk_widget_set_double_buffered (video_window, FALSE);
  g_signal_connect (a->stream.video_area, "realize", G_CALLBACK (realize_cb), data);
  g_signal_connect (a->stream.video_area, "draw", G_CALLBACK (draw_cb), data);

/*play_button = gtk_button_new_from_icon_name ("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR);
  g_signal_connect (G_OBJECT (play_button), "clicked", G_CALLBACK (play_cb), data);

  pause_button = gtk_button_new_from_icon_name ("media-playback-pause", GTK_ICON_SIZE_SMALL_TOOLBAR);
  g_signal_connect (G_OBJECT (pause_button), "clicked", G_CALLBACK (pause_cb), data);
*/




  a->stream.label_name = gtk_label_new ("stream to XMCarL");

	a->stream.img = gtk_image_new_from_file ("img/xmcarl.png");
gtk_widget_show_all(a->stream.img);


  a->stream.button = gtk_button_new_with_label("Start Car");
  gtk_widget_set_size_request(a->stream.button, 300, 100);
  g_signal_connect(a->stream.button, "clicked", G_CALLBACK(stream_screen_visible), (gpointer) a);


  gtk_box_pack_start (GTK_BOX(a->stream.layout), a->stream.button, FALSE, FALSE, 0);	
	

  gtk_box_pack_start (GTK_BOX(a->stream.layout), a->stream.label_name, FALSE, FALSE, 0);	
  gtk_box_pack_start (GTK_BOX(a->stream.layout), a->stream.img, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX(a->main_box), a->stream.layout, FALSE, FALSE, 0);


}




/* This function is called everytime the video window needs to be redrawn (due to damage/exposure,
 * rescaling, etc). GStreamer takes care of this in the PAUSED and PLAYING states, otherwise,
 * we simply draw a black rectangle to avoid garbage showing up. */
/*static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, CustomData *data) {
  if (data->state < GST_STATE_PAUSED) {
    GtkAllocation allocation;

    /* Cairo is a 2D graphics library which we use here to clean the video window.
     * It is used by GStreamer for other reasons, so it will always be available to us.
    gtk_widget_get_allocation (widget, &allocation);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
    cairo_fill (cr);
  }

  return FALSE;
}
*/

