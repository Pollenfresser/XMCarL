/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified:
 *
 * Date of creation: 02.01.2018
 *
 * File description: Connection over bluetooth with car
 *
 * Status: done
 * TODO: maybe check, if really 9 devices can be created (logic)
 *
 */

#include <gui_main.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

/*
 * car screen is now visible
 */
void car_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;

	gtk_widget_show_all(a->car.layout);

	gtk_widget_set_visible(a->home.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);
	gtk_widget_set_visible(a->status.layout, FALSE);

}

/*
 * here everything from stream screen should be cleaned up
 * unref, ...
 */
void car_screen_clean(gpointer data) {
	// close thread??
}

/*
 * Initialisation of car screen
 */
void car_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->car.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	a->car.button = gtk_button_new_with_label(
			"Click and wait to load devices");
	g_signal_connect(a->car.button, "clicked",
			G_CALLBACK(car_bluetooth), (gpointer) a);

	a->car.label = gtk_label_new("Please wait for available devices");
	gtk_box_pack_start(GTK_BOX(a->car.layout), a->car.label, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(a->car.layout), a->car.button, FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(a->main_box), a->car.layout, FALSE, FALSE, 0);

}

/*
 * after clicking the load devices button, this function is called
 * a button for each device will be created
 */
void car_bluetooth(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	int count_devices = 0;
	count_devices = blue_search_for_available_devices((gpointer) a);
	car_create_button_for_each_device(count_devices, (gpointer) a);
}

/*
 * Bluetooth thread calls the send data function
 * the steering and throttle value will be sent to the car over bluetooth
 */
gpointer bluetoothThread(gpointer data) {
	widgets *a = (widgets *) data;
	g_timeout_add(SENSOR_REFRESH_CYCLE, (GSourceFunc) blue_send_data,
			(gpointer) a);
	return NULL;
}

/*
 * gets selected device and starts thread for sending data over
 * bluetooth to the car
 */
void car_connect_device(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	a->choosen_blue_dev = 0;
	a->choosen_blue_dev = atoi(gtk_widget_get_name(wid));
	printf("Choosen device id: %d", a->choosen_blue_dev);
	blue_comm_init((gpointer) a);

	GThread* gthread_blue;
	gthread_blue = g_thread_new("bluetooth_data_trans",
			(GThreadFunc) bluetoothThread, (gpointer) a);
	g_thread_join(gthread_blue);

	home_screen_visible((gpointer) a);

}

/*
 * A button for each bluetooth device is created
 * the maximum is 9 (please check)
 * another button "example" is there; just for testing reasons
 */
void car_create_button_for_each_device(int count_devices, gpointer data) {

	widgets *a = (widgets *) data;
	GtkWidget *device_buttons[count_devices];
	int i;
	char c[1];
	if (count_devices > 9) {
		count_devices = 9;
	}
	for (i = 0; i < count_devices; i++) {
		device_buttons[i] = gtk_button_new_with_label(a->bluetooth[i].name);
		c[0] = i + 48;
		gtk_widget_set_name(device_buttons[i], c);
		g_signal_connect(device_buttons[i], "clicked",
				G_CALLBACK(car_connect_device), (gpointer) a);
		gtk_box_pack_start(GTK_BOX(a->car.layout), device_buttons[i], FALSE,
				FALSE, 0);
	}
	i++;
	device_buttons[i] = gtk_button_new_with_label("example");
	c[0] = i + 48;
	gtk_widget_set_name(device_buttons[i], c);
	g_signal_connect(device_buttons[i], "clicked",
			G_CALLBACK(car_connect_device), (gpointer) a);
	gtk_box_pack_start(GTK_BOX(a->car.layout), device_buttons[i], FALSE, FALSE,
			0);

	gtk_widget_show_all(a->car.layout);

}

