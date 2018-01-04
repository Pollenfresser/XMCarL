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

	widgets *a = (widgets *) data;
	int count_devices = 0;

	count_devices = blue_search_for_available_devices((gpointer) a);
	wait_create_button_for_each_device(count_devices, (gpointer) a);

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

	a->wait.button = gtk_button_new_with_label("Click and wait to load devices");
	g_signal_connect(a->wait.button, "clicked",
							G_CALLBACK(wait_screen_bluetooth), (gpointer) a);

	// you can give your functions here
	wait_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->wait.layout), a->wait.button, FALSE, FALSE, 0);
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

void wait_create_button_for_each_device(int count_devices, gpointer data){

	widgets *a = (widgets *) data;
	GtkWidget *device_buttons [count_devices];// ** -> has to be allocated
	int i;
	for(i = 0; i<count_devices; i++){
		device_buttons[i] = gtk_button_new_with_label(a->bluetooth[i].name);
		g_signal_connect(device_buttons[i], "clicked", G_CALLBACK(stream_screen_visible), (gpointer) a);
		gtk_box_pack_start(GTK_BOX(a->wait.layout), device_buttons[i], FALSE, FALSE, 0);
	}
	gtk_widget_show_all(a->wait.layout);

}

