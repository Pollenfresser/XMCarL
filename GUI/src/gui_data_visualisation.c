/**
 * Project: XMCarL
 *
 * Author: Christina Bornberg
 * Modified: Lucas Ullrich
 *
 * Date of creation: 26.12.2017
 *
 * File description: Lucas should do the data visualisation
 *
 * Status: init is done
 *
 */

#include <gui_main.h>


/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// give the prototype to header if you got a right name for it
void datavis_code(gpointer data);

void datavis_screen_visible(GtkWidget *wid, gpointer data) {
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->datavis.layout);

	gtk_widget_set_visible(a->start.layout, FALSE);
	  	gtk_widget_set_visible(a->stream.layout, FALSE);

}

// here everything from datavis screen should be cleaned up
// unref, ...
void datavis_screen_clean(gpointer data){

}

void datavis_screen_init(gpointer data) {

	widgets *a = (widgets *) data;
	a->datavis.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// you can call your functions here
	datavis_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->datavis.layout, FALSE, FALSE,
			0);

}

// you can rename this function
// append with: gtk_box_pack_start (GTK_BOX(a->datavis.layout), any widget you want, FALSE, FALSE, 0);
void datavis_code(gpointer data){

	widgets *a = (widgets *) data;
	a->datavis.label = gtk_label_new("append your code to the a->datavis.layout");
		gtk_box_pack_start(GTK_BOX(a->datavis.layout), a->datavis.label, FALSE, FALSE,
					0);


}

