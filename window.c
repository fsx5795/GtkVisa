#include "window.h"
#include "gtkcharts.h"

static GtkWidget *charts;

void on_activate(GtkApplication *app, gpointer data)
{
	GtkWidget *window = gtk_application_window_new(app);
	charts = gtk_charts_new();
	struct Xrange *xrange = (struct Xrange*)data;
	gtk_charts_set_x_range(GTK_CHARTS(charts), xrange->min, xrange->max);
	gtk_charts_set_y_range(GTK_CHARTS(charts), -120, -20);

	GtkWidget *midBtns[8];
	GtkWidget *middleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	for (int i = 0; i < sizeof midBtns / sizeof midBtns[0]; ++i) {
		midBtns[i] = gtk_button_new();
		gtk_box_append(GTK_BOX(middleBox), midBtns[i]);
		gtk_widget_set_hexpand(midBtns[i], true);
	}

	GtkWidget *freqBtn = gtk_button_new_with_label("Freq");
	GtkWidget *spanBtn = gtk_button_new_with_label("Span");
	GtkWidget *amptBtn = gtk_button_new_with_label("Ampt");
	GtkWidget *topGrid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(topGrid), freqBtn, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(topGrid), spanBtn, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(topGrid), amptBtn, 2, 0, 1, 1);

	GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_hexpand(charts, true);
	gtk_box_append(GTK_BOX(hbox), charts);
	gtk_box_append(GTK_BOX(hbox), middleBox);
	gtk_box_append(GTK_BOX(hbox), topGrid);
	gtk_window_set_child(GTK_WINDOW(window), hbox);
	gtk_widget_show(window);
	return;
}
void show_data(struct Point *pt, int len)
{
	if (charts != NULL)
		gtk_charts_set_fpc_data(GTK_CHARTS(charts), pt, len);
	return;
}