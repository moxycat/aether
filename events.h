#ifndef _EVENT_H_
#define _EVENT_H_

#include <stdio.h>
#include "entity.h"

#define EVENT_BATTLE 1
#define EVENT_CHECKPOINT 2

typedef struct _event {
    int type;
} event_t;

/* creates a battle between the player and an enemy */
void event_battle(player_state_t *pst, enemy_state_t *est);

/* restores hp of player */
void event_checkpoint(player_state_t *pst);

#endif