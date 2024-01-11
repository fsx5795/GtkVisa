#ifndef GTKCHARTS_H
#define GTKCHARTS_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "data.h"

#define GTK_CHARTS_TYPE (gtk_charts_get_type())
#define GTK_CHARTS(obj) (G_TYPE_CHECK_INSTANCE_CAST(obj, GTK_CHARTS_TYPE, GtkCharts))

typedef struct _GtkCharts GtkCharts;
struct _GtkCharts
{
    GtkDrawingArea parent;
    struct Points *points;
};

typedef struct _GtkChartsClass GtkChartsClass;
struct _GtkChartsClass
{
    GtkDrawingAreaClass parentClass;
    void (*draw_update)(void);
};

extern GType gtk_charts_get_type(void);
extern GtkWidget* gtk_charts_new(void);
extern void gtk_charts_set_x_range(GtkCharts*, double, double);
extern void gtk_charts_set_y_range(GtkCharts*, double, double);
extern void gtk_charts_set_fpc_data(GtkCharts*, struct Point*, size_t);
extern void gtk_charts_set_data(GtkCharts*, struct Point*, size_t);

#endif