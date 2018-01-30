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

void home_screen_visible(gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->home.layout);

	gtk_widget_set_visible(a->car.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);
//	gtk_widget_set_visible(a->status.layout, FALSE);

}

// here everything from start screen should be cleaned up
// unref, ...
void home_screen_clean(gpointer data) {

}

void home_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->home.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	a->home.label = gtk_label_new("Welcome to XMCarL");

	a->home.button_car = gtk_button_new_with_label("Connect car");
	gtk_widget_set_size_request(a->home.button_car, 50, 50);
	g_signal_connect(a->home.button_car, "clicked",
			G_CALLBACK(car_screen_visible), (gpointer) a);

	a->home.button_stream = gtk_button_new_with_label("Open Stream");
	gtk_widget_set_size_request(a->home.button_stream, 50, 50);
	g_signal_connect(a->home.button_stream, "clicked",
			G_CALLBACK(stream_screen_visible), (gpointer) a);

	a->home.button_datavis = gtk_button_new_with_label(
			"Remote Control Visualisation");
	gtk_widget_set_size_request(a->home.button_datavis, 50, 50);
	g_signal_connect(a->home.button_datavis, "clicked",
			G_CALLBACK(datavis_screen_visible), (gpointer) a);

	a->home.button_status = gtk_button_new_with_label("Status of devices");
	gtk_widget_set_size_request(a->home.button_status, 50, 50);
	g_signal_connect(a->home.button_status, "clicked",
			G_CALLBACK(status_screen_visible), (gpointer) a);

	a->home.img = gtk_image_new_from_file("img/xmcarl_logo.jpeg");

	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.img, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.button_car, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.button_stream, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.button_datavis, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->home.layout), a->home.button_status, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->main_box), a->home.layout, FALSE, FALSE, 0);
}
