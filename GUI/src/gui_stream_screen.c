/**
 * Project: XMCarL
 *
 * Author: Christina
 * Modified:
 * Used Code:
 *
 * Date of creation: 26.12.2017
 *
 * File description: GoPro Stream
 *
 * Status: at the beginning
 * - info: /live/amba.m3u8
 */

#include <gui_main.h>
#include <gio/gio.h>

static gboolean stream_refresh(gpointer data);
static void stream_realize_cb(GtkWidget *widget, gpointer data);


/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void stream_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	g_print("stream_screen_visible\n");

	gtk_widget_show_all(a->stream.layout);

	gtk_widget_set_visible(a->home.layout, FALSE);
	gtk_widget_set_visible(a->car.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

	// GOPRO
	stream_start_stream((gpointer) a);
}

// here everything from stream screen should be cleaned up
// unref, ...
// TODO Gtk-CRITICAL **: gtk_main_quit: assertion 'main_loops != NULL' failed
void stream_screen_clean(gpointer data) {
	widgets *a = (widgets *) data;
	g_print("stream_screen_clean\n");
	//if(main_loops != NULL){
		gst_element_set_state(a->stream.playbin, GST_STATE_READY);
		gtk_main_quit();
		gst_object_unref(a->stream.playbin);
//	}
}

int stream_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	// pipeline == playbin

	g_print("stream_screen_init\n");
	a->stream.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(a->main_box), a->stream.layout);

	gtk_init(NULL, NULL); // Initialize GTK
	gst_init(NULL, NULL); // Initialize GStreamer

	a->stream.source = gst_element_factory_make("udpsrc", "udp");
	a->stream.sink = gst_element_factory_make ("autovideosink", "sink");

	a->stream.playbin = gst_element_factory_make("playbin", "playbin");
	if (!a->stream.playbin || !a->stream.source || !a->stream.sink) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	a->stream.video_window = gtk_drawing_area_new();
	gtk_widget_set_size_request (a->stream.video_window, 700, 500);
	g_signal_connect(a->stream.video_window, "realize", G_CALLBACK(stream_realize_cb),
				(gpointer) a);
	gtk_container_add(GTK_CONTAINER(a->stream.layout), a->stream.video_window);
	return 0;
}

static gboolean stream_refresh(gpointer data) {
	return TRUE;
}

void stream_start_stream(gpointer data) {
	widgets *a = (widgets *) data;
	g_print("stream_start_stream\n");

	GstStateChangeReturn ret;

	//g_object_set(a->stream.playbin, "uri", 			"udp://:8554",			NULL);

//	GSocket *goproSocketUpd;
//
//	goproSocketUpd = g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_DATAGRAM, G_SOCKET_PROTOCOL_UDP, NULL);
//
	g_object_set(a->stream.playbin, "uri", "udp://:8554", NULL);

	ret = gst_element_set_state(a->stream.playbin, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		home_screen_visible((gpointer) a);
		// gst_object_unref(a->stream.playbin);
	}else {
		g_print("pipeline is on playing state");
	}

	// Register a function that GLib will call every second
	g_timeout_add_seconds(1, (GSourceFunc) stream_refresh, (gpointer) a);

	// Start the GTK main loop until gtk_main_quit TODO
	gtk_main();
}

static void stream_realize_cb(GtkWidget *widget, gpointer data) {
	widgets *a = (widgets *) data;
	g_print("stream_realize_cb\n");

	GdkWindow *gdk_window = gtk_widget_get_window(widget);
	guintptr window_handle;

	if (!gdk_window_ensure_native(gdk_window))
		g_error("Couldn't create native window needed for GstVideoOverlay!");

	/* Retrieve window handler from GDK */
#if defined (GDK_WINDOWING_WIN32)
	window_handle = (guintptr)GDK_WINDOW_HWND (gdk_window);
#elif defined (GDK_WINDOWING_QUARTZ)
	window_handle = gdk_quartz_window_get_nsview (gdk_window);
#elif defined (GDK_WINDOWING_X11)
	window_handle = GDK_WINDOW_XID (gdk_window);
#endif
	/* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(a->stream.playbin),
			window_handle);
}
