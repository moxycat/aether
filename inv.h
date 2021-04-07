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

static char *item_names[] = {
    "Potion of healing",
    "Potion of strength",
    "Potion of defense",
    "Potion of vision",
    "Apple",
    "Pickaxe",
    "Ore"
};
#define ITEM_COUNT sizeof(item_names) / sizeof(char*)

#define USAGE_CONSUMABLE 0xf0
#define USAGE_WEAPON 0xf1
#define USAGE_POTION 0xf2

typedef struct _item {
    char *name;
    int quantity;
    int dmg;
    int hp;
    int usage;
} item_t;

typedef struct _inventory {
    item_t items[ITEM_COUNT];
    int equipped;
} inventory_t;

/* draws the inventory over the current frame */
void inventory_draw(HANDLE con, inventory_t *inv);
int inventory_calc_size(inventory_t *inv);
void inventory_init(inventory_t *inv, int quantities[]);

/*method for dropping items on victory*/
void drops(HANDLE con, inventory_t *inv);


#endif