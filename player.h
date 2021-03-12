#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "mapgen.h"
#include "const.h"

/* places the player at a random location on the map */
void spawn_player(world_t *w);
/* moves the player up one cell */
void move_up(world_t *w);
/* moves the player down one cell */
void move_down(world_t *w);
/* moves the player one cell to the left */
void move_left(world_t *w);
/* moves the player one cell to the right */
void move_right(world_t *w);
/* # -> % -> . */
void break_wall(world_t *w, int dir);
/* fight an enemy in the world */
void fight_enemy(world_t *w);

#endif