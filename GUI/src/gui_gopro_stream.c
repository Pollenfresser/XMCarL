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

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// give the prototype to header if you got a right name for it
void stream_code(gpointer data);

void stream_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->stream.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->wait.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

	//stream_code((gpointer) a);
	// not working if menu because widget name
	// printf("%d", a->wait.device_id);
	a->choosen_blue_dev = 0;
	a->choosen_blue_dev = atoi(gtk_widget_get_name(wid));
	printf("Choosen device id: %d", a->choosen_blue_dev);
	blue_communication((gpointer) a);

	//bluetooth_client();

}

// here everything from stream screen should be cleaned up
// unref, ...
void stream_screen_clean(gpointer data) {

}

void stream_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->stream.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// you can give your functions here
	stream_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->stream.layout, FALSE, FALSE, 0);

}

void stream_code(gpointer data) {

	widgets *a = (widgets *) data;
	GtkWidget *video_window;

	a->stream.label = gtk_label_new("append your code to the a->stream.layout");

	video_window = gtk_drawing_area_new();

	gtk_box_pack_start(GTK_BOX(a->stream.layout), video_window, FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(a->stream.layout), a->stream.label, FALSE, FALSE,
			0);

}

