#ifndef _INV_H_
#define _INV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "mapgen.h"
#include "util.h"
#include "const.h"

/* items defined in the game */


#define ITEM_HEAL_POTION 0
#define ITEM_TORCH 1
#define ITEM_APPLE 2

static char *item_names[] = {
    "Potion of healing",
    "Potion of strength",
    "Potion of defense",
    "Potion of vision",
    "Apple"
};
#define ITEM_COUNT sizeof(item_names) / sizeof(char*)

typedef struct _inventory {
    int inv[ITEM_COUNT];
    int equipped;
    int size;
} inventory_t;

/* draws the inventory over the current frame */
void inventory_draw(HANDLE con, inventory_t *inv);
void inventory_calc_size(inventory_t *inv);

#endif