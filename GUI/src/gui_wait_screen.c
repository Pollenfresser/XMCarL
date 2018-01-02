/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified:
 *
 * Date of creation: 02.01.2018
 *
 * File description: Wait Screen - connection with GoPro
 *
 * Status: at the beginning
 *
 */

#include <gui_main.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// give the prototype to header if you got a right name for it
void wait_code(gpointer data);

void wait_screen_bluetooth(GtkWidget *wid, gpointer data) {

	blue_search_for_available_devices();

}

void wait_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;

	gtk_button_set_label (GTK_BUTTON(a->start.button), "Wait for connection");

	gtk_widget_show_all(a->wait.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

}

// here everything from stream screen should be cleaned up
// unref, ...
void wait_screen_clean(gpointer data){

}

void wait_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->wait.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	a->wait.buttons = gtk_button_new_with_label("Click for loading devices");

	// you can give your functions here
	wait_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->wait.layout, FALSE, FALSE, 0);

}

// you can rename this function
// append with: gtk_box_pack_start (GTK_BOX(a->stream.layout), any widget you want, FALSE, FALSE, 0);

void wait_code(gpointer data) {

	widgets *a = (widgets *) data;

	a->wait.label = gtk_label_new("Please wait for available devices");

	gtk_box_pack_start(GTK_BOX(a->wait.layout), a->wait.label, FALSE, FALSE,
			0);
}

