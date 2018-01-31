/**
 * Project: XMCarL
 *
 * Author: Dominik
 * Modified:
 *
 * Date of creation: 26.12.2017
 *
 * File description:
 *
 * Status: init is done
 *
 */

#include <gui_main.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

/******************************************************************************
 * Start of user functions
 *****************************************************************************/

// give the prototype to header if you got a right name for it
void datavis_code(gpointer data);

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
    gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
  gint x = 40,i,y = 32.5;

  time_t t;
  int a,b;

  srand((unsigned)time(&t));

   a = rand()%400;
   b = rand()%400;


  cairo_set_source_rgb(cr, 255, 255, 255);

  //Rectangle
  cairo_rectangle(cr, 0, 0, 800, 650);
  cairo_set_line_width(cr, 10);
  cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
  cairo_stroke(cr);
  //Top to Bottom
  cairo_move_to(cr, 0, 325);
  cairo_line_to(cr, 800, 325);
  cairo_set_line_width(cr, 2.5);
  cairo_stroke(cr);
  //Right to Left
  cairo_move_to(cr, 400, 0);
  cairo_line_to(cr, 400, 650);
  cairo_set_line_width(cr, 2.5);
  cairo_stroke(cr);

  cairo_set_line_width(cr,2.5);

  for (i = 0; i < 18; i++)
  {
    cairo_move_to(cr, x, 305);
    cairo_line_to(cr, x, 345);
    cairo_stroke(cr);

    x = x + 40;
    if(i == 8)
    {
      x = x + 40;
    }
  }


  for (i = 0; i < 18; i++)
  {
    cairo_move_to(cr, 380, y);
    cairo_line_to(cr, 420, y);
    cairo_stroke(cr);

    y = y + 32.5;
    if(i == 8)
    {
      y = y + 32.5;
    }
  }

  cairo_translate(cr, a, b);
  cairo_arc(cr, 0, 0, 15, 0, 2*3.1415);
  cairo_stroke_preserve(cr);
  cairo_set_source_rgb(cr, 0.5, 0, 0);
  cairo_fill(cr);

}


void datavis_screen_visible(GtkWidget *widget, gpointer data)
{
	widgets *a = (widgets *) data;
	gtk_widget_show_all(a->datavis.layout);

	gtk_widget_set_visible(a->home.layout, FALSE);
	gtk_widget_set_visible(a->car.layout, FALSE);
	gtk_widget_set_visible(a->stream.layout, FALSE);
	gtk_widget_set_visible(a->status.layout, FALSE);

}

// here everything from datavis screen should be cleaned up
// unref, ...
void datavis_screen_clean(gpointer data)
{

}
void print_hello (GtkWidget *widget, gpointer   data)
{
  GtkWidget *darea_new;
  widgets *a = (widgets *) data;

  g_print ("MOVE DAMN IT!!!\n");
  g_signal_connect(G_OBJECT(darea_new), "draw", G_CALLBACK(on_draw_event), NULL);
  //g_signal_connect(a->datavis.layout, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_box_pack_start(GTK_BOX(a->datavis.layout), darea_new, FALSE, FALSE, 0);
}

void datavis_screen_init(gpointer data)
{
  widgets *a = (widgets *) data;
	a->datavis.layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// you can call your functions here
	// uart call function
	datavis_code((gpointer) a);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->datavis.layout, FALSE, FALSE,0);

}


// you can rename this function
// append with: gtk_box_pack_start (GTK_BOX(a->datavis.layout), any widget you want, FALSE, FALSE, 0);
void datavis_code( gpointer data)
{
  GtkWidget *darea;
  widgets *a = (widgets *) data;
  GtkWidget *button;

  darea = gtk_drawing_area_new();
  gtk_widget_set_size_request(darea, 800, 650);

  button = gtk_button_new_with_label ("Move");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_container_add (GTK_CONTAINER (a->datavis.layout), button);

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
//  g_signal_connect(a->datavis.layout, "destroy", G_CALLBACK(gtk_main_quit), NULL);


	gtk_box_pack_start(GTK_BOX(a->datavis.layout), darea, FALSE, FALSE, 0);

}
