/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 *
 * Date of creation: 26.12.2017
 *
 * File description: Menu
 *
 * Status:
 * TODO if you are not connected already - connect and show wait screen
 *
 */

#include <gui_main.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

const GActionEntry app_entries[] = { { "end", menu_callback_end, NULL, NULL,
NULL, { 0, 0, 0 } }, { "stream", menu_callback_stream, NULL, NULL, NULL, { 0, 0,
		0 } },
		{ "visual", menu_callback_visual, NULL, NULL, NULL, { 0, 0, 0 } }, {
				"about", menu_callback_about, NULL, NULL, NULL, { 0, 0, 0 } } };

void menu_visible(gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->menu.menubar);
}

void menu_init(gpointer data) {
	widgets *a = (widgets *) data;

	GMenu *menu, *menu_end, *menu_screen, *menu_about;

	// keyboard accelerators
	const gchar *accels_end[8] = { "<Ctrl>e", NULL };
	const gchar *accels_stream[8] = { "<Ctrl>s", NULL };
	const gchar *accels_visual[8] = { "<Ctrl>v", NULL };
	const gchar *accels_about[2] = { "F1", NULL };

	// map entries and actions *****
	g_action_map_add_action_entries(G_ACTION_MAP(a->app), app_entries,
			G_N_ELEMENTS(app_entries), (gpointer) a);

	// create the menu *****
	menu = g_menu_new();

	// create menu end ****
	menu_end = g_menu_new();
	g_menu_append(menu_end, "End", "app.end"); // quit

	// create menu screens *****
	menu_screen = g_menu_new();
	g_menu_append(menu_screen, "Stream - not working", "app.stream"); // gopro stream
	g_menu_append(menu_screen, "Visual", "app.visual"); // data visualisation
	g_menu_append_section(menu_end, NULL, G_MENU_MODEL(menu_screen));

	g_menu_insert_submenu(menu, 0, "Screens", G_MENU_MODEL(menu_end));

	g_object_unref(menu_screen);
	g_object_unref(menu_end);

	// create menu info *****
	menu_about = g_menu_new();
	g_menu_append(menu_about, "About", "app.about");
	g_menu_append_submenu(menu, "Info", G_MENU_MODEL(menu_about));
	g_object_unref(menu_about);

	// add menus to menu bar *****
	a->menu.menubar = gtk_menu_bar_new_from_model(G_MENU_MODEL(menu));
	gtk_box_pack_start(GTK_BOX(a->main_box), a->menu.menubar, FALSE, FALSE, 0);

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action(GTK_APPLICATION(a->app), "app.end",
			accels_end);
	gtk_application_set_accels_for_action(GTK_APPLICATION(a->app), "app.stream",
			accels_stream);
	gtk_application_set_accels_for_action(GTK_APPLICATION(a->app), "app.visual",
			accels_visual);
	gtk_application_set_accels_for_action(GTK_APPLICATION(a->app), "app.about",
			accels_about);

}

void menu_callback_end(GSimpleAction *action, GVariant *parameter,
		gpointer data) {
	widgets *a = (widgets *) data;
	start_screen_visible((gpointer) a);
}

void menu_callback_stream(GSimpleAction *action, GVariant *parameter,
		gpointer data) {
	widgets *a = (widgets *) data;
	stream_screen_visible(NULL, (gpointer) a);
}

void menu_callback_visual(GSimpleAction *action, GVariant *parameter,
		gpointer data) {
	widgets *a = (widgets *) data;
	datavis_screen_visible(NULL, (gpointer) a);
}

void menu_callback_about(GSimpleAction *action, GVariant *parameter,
		gpointer data) {
	widgets *a = (widgets *) data;
	GdkPixbuf *pixbuf;
	GtkWidget *about_dialog;
	const gchar *authors[] = { "Christina Bornberg", "Lucas Ullrich", NULL };

	// Image
	pixbuf = gdk_pixbuf_new_from_file("img/xmcarl.png", NULL);

	// Layout
	about_dialog = gtk_about_dialog_new();

	gtk_show_about_dialog(GTK_WINDOW(a->window), "program-name", "XMCarL",
			"version", "1.0", "copyright", "Copyright \xc2\xa9 EleVariation",
			"comments", "An application by some beginner-developers", "authors",
			authors, "logo", pixbuf,
			NULL);

	g_signal_connect(GTK_DIALOG(about_dialog), "response",
			G_CALLBACK(destroy_dialog), (gpointer) a);

	// Free
	g_object_unref(pixbuf);

}

void destroy_dialog(GtkDialog *dialog, gint response_id, gpointer data) {
	gtk_widget_destroy(GTK_WIDGET(dialog));
}
