#ifndef _INV_H_
#define _INV_H_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "mapgen.h"
#include "util.h"
#include "const.h"

typedef struct _item {
    char *name;
    int quantity;
} item_t;

typedef struct _inventory {
    item_t a;
    item_t b;
    item_t c;
} inventory_t;

/* draws the inventory over the current frame */
void inventory_draw(inventory_t *inv);

#endif