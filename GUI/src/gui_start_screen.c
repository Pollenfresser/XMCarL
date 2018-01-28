/**
 * Project: XMCarL
 *
 * Author: Lucas Ullrich
 * Modified: Christina Bornberg
 *
 * Date of creation: 26.12.2017
 *
 * File description: Start Screen
 *
 * Status: done
 *
 */

#include <gui_main.h>


/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void start_screen_visible(gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->start.layout);

	gtk_widget_set_visible(a->wait.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);
}

// here everything from start screen should be cleaned up
// unref, ...
void start_screen_clean(gpointer data){

}

void start_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->start.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	a->start.label = gtk_label_new("Welcome to XMCarL");

	a->start.button = gtk_button_new_with_label("Connect car");
	gtk_widget_set_size_request(a->start.button, 50, 50);
	g_signal_connect(a->start.button, "clicked",
			G_CALLBACK(wait_screen_visible), (gpointer) a);

	a->start.img = gtk_image_new_from_file("img/xmcarl_logo.jpeg");

	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.label, FALSE,
				FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.img, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.button, FALSE, FALSE,
				0);
	gtk_box_pack_start(GTK_BOX(a->main_box), a->start.layout, FALSE, FALSE, 0);
}
