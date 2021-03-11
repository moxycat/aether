#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <stdio.h>
#include <iostream>
#include "util.hpp"
#include "const.hpp"
using namespace std;

typedef struct _player_state {
    int hp_curr;
    int dmg_base; /*the damage an enemy will take after all random modifiers/bonuses*/
    int defence;
    int dmg_vary;
    bool defending; /* the player will take reduced damage if this is true */
    bool escape = false;
} player_state_t;

typedef struct _enemy_state {
    int hp_curr;
    int dmg_base;
    int dmg_vary;
    int defence;
} enemy_state_t;

/* player functionality */

/* deals dmg to enemy */
void player_attack(player_state_t *pst, enemy_state_t *est);

int player_dmg_fin(player_state_t *pst); //calculates the damage that enemies will take

/* enemy functionality */

/* generates an enemy */
enemy_state_t enemy_generate();

int enemy_dmg_fin(enemy_state_t *pst);

/* deals dmg to player */
void enemy_attack(player_state_t *pst, enemy_state_t *est);

#endif
