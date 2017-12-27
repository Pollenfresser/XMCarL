#include <gui_main.h>

void start_screen_visible(gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->start.layout);

	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->datavis.layout, FALSE);
}

void start_screen_init(gpointer data) {
	widgets *a = (widgets *) data;

	a->start.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	a->start.label_name = gtk_label_new("Welcome to XMCarL");

	a->start.img = gtk_image_new_from_file("img/xmcarl.png");
	gtk_widget_show_all(a->start.img);

	a->start.button = gtk_button_new_with_label("Start driving!");
	gtk_widget_set_size_request(a->start.button, 100, 100);
	g_signal_connect(a->start.button, "clicked",
			G_CALLBACK(stream_screen_visible), (gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.button, FALSE, FALSE,
			0);

	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.label_name, FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->start.layout), a->start.img, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(a->main_box), a->start.layout, FALSE, FALSE, 0);

}
