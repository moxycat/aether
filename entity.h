#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdio.h>
#include "util.h"

typedef struct _player_state {
    int32_t hp;
    int32_t dmg;
} player_state_t;

typedef struct _enemy_state {
    int32_t hp;
    int32_t dmg;
} enemy_state_t;

/* player functionality */

/* deals dmg to enemy */
uint32_t player_attack(player_state_t *pst, enemy_state_t *est);
/* reduces the dmg multiplier of the enemy for 1 turn */
void player_defend(player_state_t *pst, enemy_state_t *est);


/* enemy functionality*/

/* generates an enemy */
enemy_state_t *enemy_generate();
/* deals dmg to player */
uint32_t enemy_attack(enemy_state_t *est, player_state_t *pst);

#endif