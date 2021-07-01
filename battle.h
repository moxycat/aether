#ifndef _BATTLE_H_
#define _BATTLE_H_

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "mapgen.h"
#include "global.h"
#include "player.h"
#include "inv.h"

void battle(HANDLE con, entity_t *player, inventory_t *inv, int choice);
void victory(HANDLE con, entity_t *player, entity_t *enemy, inventory_t *inv, int choice);
void defeat(HANDLE con, int choice);
void player_turn(HANDLE con, entity_t *player, entity_t *enemy, int choice);
int enemy_turn(HANDLE con, entity_t *player, entity_t *enemy, int choice);

#endif