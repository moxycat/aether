#ifndef _MAPGEN_H_
#define _MAPGEN_H_

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "util.h"

/*
    contains info about the world, i.e. the map, player position
    depth should be added at some point as well
*/
typedef struct _world {
    char map[ROWS][COLS];
    int player_x;
    int player_y;
    int depth;
} world_t;

/*
    initial map creation
    each cell has a 45% probability of being a wall
    otherwise it's floor
*/
void map_init(char map[ROWS][COLS]);

/*
    counts the number of walls around a given cell
    X X X
    X O X
    X X X
    counts how many of the Xs are walls
*/
int map_tile_neighbours(char map[ROWS][COLS], int x, int y);

/* gives the next iteration of the map after applying the rules once */
void map_step(char map[ROWS][COLS]);

/* applies map_step n times */
void map_iter(char map[ROWS][COLS], int n);

#endif