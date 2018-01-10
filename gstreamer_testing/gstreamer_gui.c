// gcc gstreamer_gui.c -o gstreamer_gui `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0` -Wall -g

#include <string.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include <gdk/gdk.h>
#if defined (GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined (GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif

/* Structure to contain all our information, so we can pass it around */
typedef struct _CustomData {
	GstElement *playbin; /* Our one and only pipeline */
} CustomData;

static void realize_cb(GtkWidget *widget, CustomData *data) {
	GdkWindow *window = gtk_widget_get_window(widget);
	guintptr window_handle;

	if (!gdk_window_ensure_native(window))
		g_error("Couldn't create native window needed for GstVideoOverlay!");

	/* Retrieve window handler from GDK */
	window_handle = GDK_WINDOW_XID (window);
	/* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(data->playbin),
			window_handle);
}

/* This function is called when the main window is closed */
static void delete_event_cb(GtkWidget *widget, GdkEvent *event,
		CustomData *data) {
	gst_element_set_state(data->playbin, GST_STATE_READY);
	gtk_main_quit();
}

/* This creates all the GTK+ widgets that compose our application, and registers the callbacks */
static void create_ui(CustomData *data) {
	GtkWidget *main_window; /* The uppermost window, containing all other windows */
	GtkWidget *video_window; /* The drawing area where the video will be shown */
	GtkWidget *layout; /* VBox to hold main_hbox and the controls */

	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(main_window), "delete-event",
			G_CALLBACK(delete_event_cb), data);

	video_window = gtk_drawing_area_new();
	// gtk_widget_set_double_buffered(video_window, FALSE);
	g_signal_connect(video_window, "realize", G_CALLBACK(realize_cb), data);
	//g_signal_connect(video_window, "draw", G_CALLBACK(draw_cb), data);

	layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(layout), video_window, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(main_window), layout);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 640, 480);

	gtk_widget_show_all(main_window);
}

/*
 * Window
 *  - main box
 *  	- menu
 *  	- layout box
 *  		- draw area
 */

/* This function is called periodically to refresh the GUI */
static gboolean refresh_ui(CustomData *data) {
//	gint64 current = -1;

	/*We do not want to update anything unless we are in the PAUSED or PLAYING states */
	//if (data->state < GST_STATE_PAUSED)
		//return TRUE;

	return TRUE;
}

int main(int argc, char *argv[]) {
	CustomData data;
	GstStateChangeReturn ret;
	GstBus *bus;

	/* Initialize GTK */
	gtk_init(&argc, &argv);

	/* Initialize GStreamer */
	gst_init(&argc, &argv);

	/* Initialize our data structure */
	memset(&data, 0, sizeof(data));

	/* Create the elements */
	data.playbin = gst_element_factory_make("playbin", "playbin");

	if (!data.playbin) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	/* Set the URI to play */
	g_object_set(data.playbin, "uri",
			"https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",
			NULL);

	/* Create the GUI */
	create_ui(&data);

	/* Instruct the bus to emit signals for each received message, and connect to the interesting signals */
//	bus = gst_element_get_bus(data.playbin);
//	gst_bus_add_signal_watch(bus);
//
//	// g_signal_connect (G_OBJECT (bus), "message::application", (GCallback)application_cb, &data);
//	gst_object_unref(bus);

	/* Start playing */
	ret = gst_element_set_state(data.playbin, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(data.playbin);
		return -1;
	}

	/* Register a function that GLib will call every second */
	g_timeout_add_seconds(1, (GSourceFunc) refresh_ui, &data);

	/* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
	gtk_main();

	/* Free resources */
	gst_element_set_state(data.playbin, GST_STATE_NULL);
	gst_object_unref(data.playbin);
	return 0;
}
