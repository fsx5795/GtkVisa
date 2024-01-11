#ifndef WINDOW_H
#define WINDOW_H

#include <gtk/gtk.h>

struct Xrange
{
	double min;
	double max;
};

extern void on_activate(GtkApplication*, gpointer);
extern void show_data(struct Point*, int);

#endif