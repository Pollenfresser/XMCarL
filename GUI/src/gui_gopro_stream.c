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

// TODO headerfile
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

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// give the prototype to header if you got a right name for it
static gboolean stream_refresh(gpointer data);
static void realize_cb(GtkWidget *widget, gpointer data);
void stream_start_stream(gpointer data);

void stream_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;

	//	gtk_window_set_default_size(GTK_WINDOW(a->window), 640, 480);

	gtk_widget_show_all(a->stream.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->wait.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

	stream_start_stream((gpointer) a);

	//stream_code((gpointer) a);
	// not working if menu because widget name
	// printf("%d", a->wait.device_id);
	//a->choosen_blue_dev = 0;
	//a->choosen_blue_dev = atoi(gtk_widget_get_name(wid));
	// printf("Choosen device id: %d", a->choosen_blue_dev);
	//blue_communication((gpointer) a);

	//bluetooth_client();

}

// here everything from stream screen should be cleaned up
// unref, ...
void stream_screen_clean(gpointer data) {

}

void stream_screen_init(gpointer data) {
	widgets *a = (widgets *) data;
	// TODO
	a->stream.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(a->main_box), a->stream.layout);
	stream_code((gpointer) a);

//	gtk_box_pack_start(GTK_BOX(a->main_box), a->stream.layout, FALSE, FALSE, 0);

//	gtk_box_pack_start(GTK_BOX(a->main_box), a->stream.layout, FALSE, FALSE, 0);
}

void stream_start_stream(gpointer data) {
	widgets *a = (widgets *) data;

	GstStateChangeReturn ret;

	g_object_set(a->stream.playbin, "uri",
			"https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",
			NULL);

	ret = gst_element_set_state(a->stream.playbin, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(a->stream.playbin);
	}

	/* Register a function that GLib will call every second */
	g_timeout_add_seconds(1, (GSourceFunc) stream_refresh, (gpointer) a);

	/* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
	gtk_main();
}

static void realize_cb(GtkWidget *widget, gpointer data) {
	widgets *a = (widgets *) data;

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

static gboolean stream_refresh(gpointer data) {
	return TRUE;
}

int stream_code(gpointer data) {

	widgets *a = (widgets *) data;

	gtk_init(NULL, NULL);
	/* Initialize GStreamer */
	gst_init(NULL, NULL);

	a->stream.playbin = gst_element_factory_make("playbin", "playbin");

	if (!a->stream.playbin) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	a->stream.video_window = gtk_drawing_area_new();
	gtk_widget_set_size_request (a->stream.video_window, 700, 500);
	g_signal_connect(a->stream.video_window, "realize", G_CALLBACK(realize_cb),
			(gpointer) a);
	gtk_container_add(GTK_CONTAINER(a->stream.layout), a->stream.video_window);

	return 0;

}

