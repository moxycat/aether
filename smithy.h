#ifndef _SMITHY_H_
#define _SMITHY_H_

#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "mapgen.h"
#include "global.h"
#include "player.h"
#include "inv.h"
#include "graphics.h"


void upgrade_menu(HANDLE con, entity_t *player, inventory_t *inv, int choice);
void upgrade_weapon(HANDLE con, entity_t *player, inventory_t *inv, int choice);
void upgrade_armour(HANDLE con, entity_t *player, inventory_t *inv, int choice);
void smithy(HANDLE con, entity_t *player, inventory_t *inv);

#endif