#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdint.h>

#include "console.h"
#include "util.h"

#define SIZE_W 75 // 95 // 80
#define SIZE_H 20 //27 // 35 // 24

#define WALL 219
#define FLOOR 32

#define PLAYER 234
#define ENEMY 153

#define PLAYER_P1 220
#define PLAYER_P2 220
#define PLAYER_P3 217
#define PLAYER_P4 192

typedef struct _map {
    uint8_t buffer[SIZE_W * SIZE_H];
    uint32_t width;
    uint32_t height;
    struct player_coords {
        uint32_t x;
        uint32_t y;
    };
} map_t;

map_t map_init();
void map_render_player(map_t *map);
void map_populate(map_t *map);
//void map_print(map_t *map);

#endif