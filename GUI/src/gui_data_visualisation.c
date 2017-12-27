#include <gui_main.h>

void datavis_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->datavis.layout);

}

void datavis_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->datavis.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	a->datavis.label_name = gtk_label_new("Welcome to XMCarL");

	a->datavis.img = gtk_image_new_from_file("img/xmcarl.png");
	gtk_widget_show_all(a->datavis.img);

	a->datavis.button = gtk_button_new_with_label("Start Car");
	gtk_widget_set_size_request(a->datavis.button, 300, 100);
	g_signal_connect(a->datavis.button, "clicked",
			G_CALLBACK(stream_screen_visible), (gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->datavis.layout), a->datavis.button, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->datavis.layout), a->datavis.label_name, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->datavis.layout), a->datavis.img, FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(a->main_box), a->datavis.layout, FALSE, FALSE,
			0);

}

