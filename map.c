#include "map.h"

map_t map_init() {
    map_t map;

    map.width = SIZE_W;
    map.height = SIZE_H;

    /* make everything floor */
    for (int i = 1; i < SIZE_W * SIZE_H; ++i) map.buffer[i] = FLOOR;

    /* add player */
    map.x = 3;
    map.y = 7;
    map_render_player(&map);
    //map.buffer[square_to_linear(map.y, map.x, SIZE_W)] = PLAYER;

    /* set borders */

    /* top border */
    for (int i = 0; i < SIZE_W; ++i) {
        map.buffer[square_to_linear(0, i, SIZE_W)] = WALL;
    }
    /* bottom border */
    for (int i = 0; i < SIZE_W; ++i) {
        map.buffer[square_to_linear(SIZE_H - 1, i, SIZE_W)] = WALL;
    }
    /* left border */
    for (int i = 0; i < SIZE_H; ++i) {
        // a[0][i]
        map.buffer[square_to_linear(i, 0, SIZE_W)] = WALL;
    }
    /* right border */
    for (int i = 0; i < SIZE_H; ++i) {
        map.buffer[square_to_linear(i, SIZE_W - 1, SIZE_W)] = WALL;
    }

    return map;
}

void map_render_player(map_t *map) {
    map->buffer[square_to_linear(map->y, map->x, SIZE_W)] = PLAYER_P1;
    map->buffer[square_to_linear(map->y, map->x + 1, SIZE_W)] = PLAYER_P2;
    map->buffer[square_to_linear(map->y + 1, map->x, SIZE_W)] = PLAYER_P3;
    map->buffer[square_to_linear(map->y + 1, map->x + 1, SIZE_W)] = PLAYER_P4;
}

void map_populate(map_t *map) {

}