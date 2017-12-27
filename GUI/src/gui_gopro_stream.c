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

void stream_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->stream.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

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

void stream_code(gpointer data) {

	widgets *a = (widgets *) data;

	a->stream.label = gtk_label_new("append your code to the a->stream.layout");

	gtk_box_pack_start(GTK_BOX(a->stream.layout), a->stream.label, FALSE, FALSE,
			0);

}

