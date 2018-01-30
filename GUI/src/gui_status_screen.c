/**
 * Project: XMCarL
 *
 * Author: Christina
 * Modified:
 * Used Code:
 *
 * Date of creation: 30.01.2018
 *
 * File description: Status of all devices
 *
 * Status: at the beginning
 */

#include <gui_main.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

void status_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;

	gtk_widget_show_all(a->status.layout);

	gtk_widget_set_visible(a->home.layout, FALSE);
	gtk_widget_set_visible(a->car.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);

	status_screen_refresh_status(a->status.label_gopro_status, a->status.gopro);
	status_screen_refresh_status(a->status.label_car_status, a->status.car);
	status_screen_refresh_status(a->status.label_remote_status,
			a->status.remote);
	status_screen_refresh_status(a->status.label_stream_status,
			a->status.stream);

	status_screen_refresh_info(a->status.label_gopro_info,
			a->status.gopro_info);
	status_screen_refresh_info(a->status.label_car_info, a->status.car_info);
	status_screen_refresh_info(a->status.label_remote_info,
			a->status.remote_info);
	status_screen_refresh_info(a->status.label_stream_info,
			a->status.stream_info);

	if (a->status.remote != ERROR) {
		gtk_widget_set_visible(a->status.button_uart_connect, FALSE);
	}
	if (a->status.gopro != ERROR) {
		gtk_widget_set_visible(a->status.button_gopro_connect, FALSE);
	}

}

// here everything from stream screen should be cleaned up
// unref, ...
void status_screen_clean(gpointer data) {

}

void status_screen_refresh_info(GtkWidget *wid, char info[1024]) {
	gtk_label_set_text(GTK_LABEL(wid), info);
}

void status_screen_refresh_status(GtkWidget *wid, int status) {
	switch (status) {
	case INIT:
		gtk_label_set_text(GTK_LABEL(wid), "Initialised");
		break;
	case CONNECTED:
		gtk_label_set_text(GTK_LABEL(wid), "Connected");
		break;
	case DISCONNECTED:
		gtk_label_set_text(GTK_LABEL(wid), "Disconnected");
		break;
	case SENDING:
		gtk_label_set_text(GTK_LABEL(wid), "Sending");
		break;
	case RECEIVING:
		gtk_label_set_text(GTK_LABEL(wid), "Receiving");
		break;
	case ERROR:
		gtk_label_set_text(GTK_LABEL(wid), "Error");
		break;
	default:
		gtk_label_set_text(GTK_LABEL(wid), "Unknown status");
		break;
	}
}

void status_call_new_uart(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;

	GThread* gthread_uart;
	gthread_uart = g_thread_new("data_transfer", (GThreadFunc) uartThread,
			(gpointer) a);
	g_thread_join(gthread_uart);
}

void status_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	GtkWidget *label_gopro;
	GtkWidget *label_car;
	GtkWidget *label_remote;
	GtkWidget *label_stream;

	a->status.gopro = INIT;
	a->status.car = INIT;
	//	a->status.remote = INIT;
	a->status.stream = INIT;
	strcpy(a->status.gopro_info, "-");
	strcpy(a->status.car_info, "-");
	//strcpy(a->status.remote_info, "-");
	strcpy(a->status.stream_info, "-");

	a->status.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	label_gopro = gtk_label_new("GoPro: ");
	a->status.label_gopro_status = gtk_label_new(" ");
	a->status.label_gopro_info = gtk_label_new(" ");

	label_car = gtk_label_new("Car: ");
	a->status.label_car_status = gtk_label_new(" ");
	a->status.label_car_info = gtk_label_new(" ");

	label_remote = gtk_label_new("Remote: ");
	a->status.label_remote_status = gtk_label_new(" ");
	a->status.label_remote_info = gtk_label_new(" ");

	label_stream = gtk_label_new("Stream: ");
	a->status.label_stream_status = gtk_label_new(" ");
	a->status.label_stream_info = gtk_label_new(" ");

	a->status.button_gopro_connect = gtk_button_new_with_label(
			"Connect GoPro again");
	gtk_widget_set_size_request(a->status.button_gopro_connect, 50, 50);
	g_signal_connect(a->status.button_gopro_connect, "clicked",
			G_CALLBACK(gopro_init), (gpointer) a);

	a->status.button_uart_connect = gtk_button_new_with_label(
			"Connect UART again");
	gtk_widget_set_size_request(a->status.button_gopro_connect, 50, 50);
	g_signal_connect(a->status.button_uart_connect, "clicked",
			G_CALLBACK(status_call_new_uart), (gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->status.layout), label_gopro, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_gopro_status,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_gopro_info,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), label_car, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_car_status,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_car_info,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), label_remote, FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_remote_status,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_remote_info,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), label_stream, FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_stream_status,
			FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.label_stream_info,
			FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(a->status.layout),
			a->status.button_gopro_connect, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->status.layout), a->status.button_uart_connect,
			FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->status.layout, FALSE, FALSE, 0);
}

