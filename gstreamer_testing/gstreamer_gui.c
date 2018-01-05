#include <string.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include <gdk/gdk.h>

// gcc gstreamer_gui.c -o gstreamer_gui `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -Wall -g

/* Structure to contain all our information, so we can pass it around */
typedef struct _CustomData {
  GstElement *playbin;           /* Our one and only pipeline */
  GtkWidget *streams_list;        /* Text widget to display info about the streams */
  GstState state;                 /* Current state of the pipeline */
  gint64 duration;                /* Duration of the clip, in nanoseconds */
} CustomData;


/* This function is called when the main window is closed */
static void delete_event_cb (GtkWidget *widget, GdkEvent *event, CustomData *data) {
	gst_element_set_state (data->playbin, GST_STATE_READY);
  gtk_main_quit ();
}

/* This creates all the GTK+ widgets that compose our application, and registers the callbacks */
static void create_ui (CustomData *data) {

g_printerr ("create ui \n");
  GtkWidget *main_window;  /* The uppermost window, containing all other windows */
  GtkWidget *video_window; /* The drawing area where the video will be shown */
  GtkWidget *main_box;     /* VBox to hold  */
//  GtkWidget *controls;     /* HBox to hold the buttons and the slider */
//  GtkWidget *play_button, *pause_button, *stop_button; /* Buttons */

/*
  main_window = gtk_application_window_new (w->app);
  	gtk_window_set_application (GTK_WINDOW (w->window), GTK_APPLICATION (w->app));
*/

  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (main_window), "delete-event", G_CALLBACK (delete_event_cb), data);

  video_window = gtk_drawing_area_new ();

  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	
gtk_box_pack_start (GTK_BOX (main_box), video_window, FALSE, FALSE, 0);

 // gtk_box_pack_start (GTK_BOX (main_box), controls, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (main_window), main_box);
  gtk_window_set_default_size (GTK_WINDOW (main_window), 1000, 480);

  gtk_widget_show_all (main_window);
}

/* This function is called periodically to refresh the GUI */
static gboolean refresh_ui (CustomData *data) {

//g_printerr ("refresh \n");
  gint64 current = -1;

  /* We do not want to update anything unless we are in the PAUSED or PLAYING states */
  if (data->state < GST_STATE_PAUSED)
    return TRUE;

  /* If we didn't know it yet, query the stream duration */
  if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
    if (!gst_element_query_duration (data->playbin, GST_FORMAT_TIME, &data->duration)) {
      g_printerr ("Could not query current duration.\n");
    } else {
    }
  }

  if (gst_element_query_position (data->playbin, GST_FORMAT_TIME, &current)) {
  
  }
  return TRUE;
}

int main(int argc, char *argv[]) {
  CustomData data;
  GstStateChangeReturn ret;
  GstBus *bus;

  /* Initialize GTK */
  gtk_init (&argc, &argv);

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Initialize our data structure */
  memset (&data, 0, sizeof (data));
  data.duration = GST_CLOCK_TIME_NONE;

  /* Create the elements */
  data.playbin = gst_element_factory_make ("playbin", "playbin");

  if (!data.playbin) {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }

  /* Set the URI to play */
  g_object_set (data.playbin, "uri", "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);

  /* Create the GUI */
  create_ui (&data);
g_printerr ("GUI init\n");

  /* Instruct the bus to emit signals for each received message, and connect to the interesting signals */
  bus = gst_element_get_bus (data.playbin);
  gst_bus_add_signal_watch (bus);
gst_object_unref (bus);

  /* Start playing */
  ret = gst_element_set_state (data.playbin, GST_STATE_PLAYING);
g_printerr ("start playing \n");


  /* Register a function that GLib will call every second */
  g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);

  /* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
  gtk_main ();

  /* Free resources */
  gst_element_set_state (data.playbin, GST_STATE_NULL);
  gst_object_unref (data.playbin);
  return 0;
}

