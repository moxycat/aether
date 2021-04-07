#ifndef _GLOBAL_H_
#define _GLOBAL_H_

static int player_max_hp = 100;
static int player_init_dmg = 5;
static int player_init_dmg_vary = 3;
static int player_inv_cap = 10;
static int inventory_initial_quantities[ITEM_COUNT] = {0, 0, 0, 0, 5, 1, 0};

static char fov_map[ROWS][COLS];
extern int cheat;

#endif