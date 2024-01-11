#ifndef FPC_H
#define FPC_H

#include <stdbool.h>
#include "data.h"

extern bool init_fpc(double*, double*, void (*)(struct Point*, int));
extern void clear_fpc(void);

#endif