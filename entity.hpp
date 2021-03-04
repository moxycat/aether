#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <stdio.h>
#include <iostream>
#include "util.hpp"
using namespace std;

typedef struct _player_state {
    int hp_curr;
    int hp_max;
    int dmg_base;
    double dmg_fin_float;
    int dmg_fin; /*the damage an enemy will take after all random modifiers/bonuses*/
    int defence;
    //int xp_curr;
    //int xp_needed;
    //int xp_excess;	
    int lvl;
    int choice;
    bool defending; /* the player will take reduced damage if this is true */
    bool escape = false;
    string name;
} player_state_t;

typedef struct _enemy_state {
    int hp_curr;
    int hp_max;
    int dmg_base;
    double dmg_fin_float;
    int dmg_fin;
    string name;
    string desc;
} enemy_state_t;

/* player functionality */

/* deals dmg to enemy */
void player_attack(player_state_t *pst, enemy_state_t *est);

/* enemy functionality */

/* generates an enemy */
enemy_state_t enemy_generate(player_state_t *pst);

/* deals dmg to player */
void enemy_attack(player_state_t *pst, enemy_state_t *est);

#endif
