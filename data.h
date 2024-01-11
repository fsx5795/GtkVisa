#ifndef DATA_H
#define DATA_H

#include <gtk/gtk.h>

struct Point
{
    double x;
    double y;
};

struct Points
{
    struct Point *pt;
    double minX;
    double minY;
    double maxX;
    double maxY;
    size_t leng;
};

extern GAsyncQueue *asyncQueue;


#endif