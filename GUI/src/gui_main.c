/**
 * Project: XMCarL
 *
 * Author: Lucas Ullrich
 * Modified: Christina Bornberg
 *
 * Date of creation: 26.12.2017
 *
 * File description: Main - routine
 *
 * Status: done so far
 *
 *	TODO: reconnect function and if menu is used: wait screen
 *	TODO: you are able to click the connect button more often than twice - this is a big problem
 *  TODO: close main loop from gstreamer
 */

#include <gui_main.h>

/**
 * Global variables
 */
/*!< UART lib */

int cport_nr = 16;    // /dev/ttyUSB0

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

/*
 * The girl loves media technology
 */
void apply_css(GtkWidget *widget, GtkStyleProvider *css_s) {
	gtk_style_context_add_provider(gtk_widget_get_style_context(widget), css_s,
			G_MAXUINT);

	if (GTK_IS_CONTAINER(widget)) {
		gtk_container_forall(GTK_CONTAINER(widget), (GtkCallback) apply_css,
				css_s);
	}
}

/*
 * Thread for UART
 * gets Data from MEMS sensor
 * Data is needed for Bluetooth connection and Data visualisation
 */
gpointer uartThread(gpointer data){
  widgets *a = (widgets *) data;

  if(pc_uart_init()) {
    return FALSE;
  }

  g_timeout_add(SENSOR_REFRESH_CYCLE, (GSourceFunc) pc_uart_receive, NULL);

  return NULL;

}

/*
 * CSS provider, Window properties, main_box - Layout, init of all screens
 * CSS function call, make screens visible
 */
void activate(GtkApplication *app, gpointer data) {
	widgets *a = (widgets *) data;
	g_print("activate\n");

	a->css_style = GTK_STYLE_PROVIDER(gtk_css_provider_new());
	gtk_css_provider_load_from_resource(GTK_CSS_PROVIDER(a->css_style),
			"/gui_res/css/style.css");

	a->window = gtk_application_window_new(a->app);
	gtk_window_set_application(GTK_WINDOW(a->window), GTK_APPLICATION(a->app));
	gtk_window_set_position(GTK_WINDOW(a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW (a->window), "XMCarL");
	gtk_window_set_default_size(GTK_WINDOW(a->window), 800, 400);
	gtk_widget_show(a->window);

	a->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show(a->main_box);
	gtk_container_add(GTK_CONTAINER(a->window), a->main_box);

	menu_init ((gpointer) a);
	home_screen_init((gpointer) a);
	car_screen_init((gpointer) a);
	stream_screen_init((gpointer) a);
	datavis_screen_init((gpointer) a);

	apply_css(a->window, a->css_style);

	menu_visible ((gpointer) a);
	home_screen_visible((gpointer) a);

	gopro_init((gpointer) a);

}

int main(int argc, char ** argv) {
	int status;
	GThread* gthread_uart;

	// Struct which contains all of the data
	widgets *a = g_malloc(sizeof(widgets));

	gthread_uart = g_thread_new("data_transfer", (GThreadFunc) uartThread, (gpointer)a);

	a->bluetooth = g_malloc(MAX_BLUETOOTH_RESPONSES*sizeof(bluetooth_data));

	a->app = gtk_application_new("org.gtk.gui", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(a->app, "activate", G_CALLBACK(activate), (gpointer) a);
	status = g_application_run(G_APPLICATION(a->app), argc, argv);

	g_thread_join (gthread_uart);

	// clean up
	stream_screen_clean((gpointer) a);
	gopro_clean((gpointer) a);
	blue_clean((gpointer) a);

	g_object_unref(a->app);
	g_free(a->bluetooth);
	g_free(a);

	return status;
}
