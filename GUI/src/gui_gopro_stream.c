/**
 * Project: XMCarL
 *
 * Author:
 * Modified:
 *
 * Date of creation: 26.12.2017
 *
 * File description: GoPro Stream - this file should be created by Dominik and Chrisy
 *
 * Status: at the beginning
 *
 */

#include <gui_main.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/



// give the prototype to header if you got a right name for it
void stream_code(gpointer data);
void stream_main(gpointer data);

void stream_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->stream.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->wait.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

	//stream_code((gpointer) a);
	// printf("%d", a->wait.device_id);
	a->choosen_blue_dev = atoi(gtk_widget_get_name (wid));
	printf("Choosen device id: %d", a->choosen_blue_dev);
	blue_how_to_communicate((gpointer)a);

	//bluetooth_client();

}

// here everything from stream screen should be cleaned up
// unref, ...
void stream_screen_clean(gpointer data){

}

void stream_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->stream.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// you can give your functions here
	stream_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->stream.layout, FALSE, FALSE, 0);

}

// you can rename this function
// append with: gtk_box_pack_start (GTK_BOX(a->stream.layout), any widget you want, FALSE, FALSE, 0);

static gboolean refresh_ui (gpointer data) {
	widgets *a = (widgets *) data;


//g_printerr ("refresh \n");
  gint64 current = -1;

  /* If we didn't know it yet, query the stream duration */
  if (!GST_CLOCK_TIME_IS_VALID (a->stream.duration)) {
    if (!gst_element_query_duration (a->stream.playbin, GST_FORMAT_TIME, &a->stream.duration)) {
      g_printerr ("Could not query current duration.\n");
    } else {
    }
  }

  if (gst_element_query_position (a->stream.playbin, GST_FORMAT_TIME, &current)) {

  }
  return TRUE;
}


void stream_code(gpointer data) {

	widgets *a = (widgets *) data;
	 GtkWidget *video_window;

	a->stream.label = gtk_label_new("append your code to the a->stream.layout");

	 video_window = gtk_drawing_area_new ();

	 gtk_box_pack_start (GTK_BOX (a->stream.layout), video_window, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(a->stream.layout), a->stream.label, FALSE, FALSE,
			0);

}

void stream_main(gpointer data){
	  //CustomData data;
	  GstStateChangeReturn ret;
	  GstBus *bus;
		widgets *a = (widgets *) data;

	  /* Initialize our data structure */
	 // memset (&data, 0, sizeof (data));
	  a->stream.duration = GST_CLOCK_TIME_NONE;

	  /* Create the elements */
	  a->stream.playbin = gst_element_factory_make ("playbin", "playbin");

	  if (!a->stream.playbin) {
	    g_printerr ("Not all elements could be created.\n");
	    return -1;
	  }

	  /* Set the URI to play */
	  g_object_set (a->stream.playbin, "uri", "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);

	  /* Create the GUI */
//	  create_ui ((gpointer)a);
//	g_printerr ("GUI init\n");

	  /* Instruct the bus to emit signals for each received message, and connect to the interesting signals */
	  bus = gst_element_get_bus (a->stream.playbin);
	  gst_bus_add_signal_watch (bus);
	gst_object_unref (bus);

	  /* Start playing */
	  ret = gst_element_set_state (a->stream.playbin, GST_STATE_PLAYING);
	g_printerr ("start playing \n");


	  /* Register a function that GLib will call every second */
	  g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &a);

	  /* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
	  gtk_main ();

	  /* Free resources */
	  gst_element_set_state (a->stream.playbin, GST_STATE_NULL);
	  gst_object_unref (a->stream.playbin);
}

