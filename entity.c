#include "entity.h"

uint32_t player_attack(player_state_t *pst, enemy_state_t *est) {
    uint32_t dmg = pst->dmg * rand_int(1, 3); /* multiplier between 1 and 2 */
    est->hp -= dmg;
    return dmg;
}

void player_defend(player_state_t *pst, enemy_state_t *est) {
    /* implement */
}

void player_move_up(map_t *map) {
    if (map->y == 0) return;

    /* these 2 are the top of the player */
    uint32_t y_old = square_to_linear(map->y, map->x, SIZE_W);
    uint32_t y1_old = square_to_linear(map->y, map->x + 1, SIZE_W);
    
    /* these 2 are the bottom of the player */
    uint32_t y2_old = square_to_linear(map->y + 1, map->x, SIZE_W);
    uint32_t y3_old = square_to_linear(map->y + 1, map->x + 1, SIZE_W);

    uint32_t y_new = square_to_linear(map->y - 1, map->x, SIZE_W);
    uint32_t y1_new = square_to_linear(map->y - 1, map->x + 1, SIZE_W);
    uint32_t y2_new = y_old;
    uint32_t y3_new = y1_old;
    if ((map->buffer[y_new] == FLOOR) && (map->buffer[y1_new] == FLOOR)) {
        map->buffer[y_old] = FLOOR;
        map->buffer[y1_old] = FLOOR;
        map->buffer[y2_old] = FLOOR;
        map->buffer[y3_old] = FLOOR;
        map->y--;
        map_render_player(map);
    }
}
void player_move_down(map_t *map) {
    if (map->y == SIZE_H - 1) return;

    /* these 2 are the top of the player */
    uint32_t y_old = square_to_linear(map->y, map->x, SIZE_W);
    uint32_t y1_old = square_to_linear(map->y, map->x + 1, SIZE_W);
    
    /* these 2 are the bottom of the player */
    uint32_t y2_old = square_to_linear(map->y + 1, map->x, SIZE_W);
    uint32_t y3_old = square_to_linear(map->y + 1, map->x + 1, SIZE_W);

    uint32_t y_new = y2_old;
    uint32_t y1_new = y3_old;
    uint32_t y2_new = square_to_linear(map->y + 1 + 1, map->x, SIZE_W);
    uint32_t y3_new = square_to_linear(map->y + 1 + 1, map->x + 1, SIZE_W);
    if ((map->buffer[y2_new] == FLOOR) && (map->buffer[y3_new] == FLOOR)) {
        map->buffer[y_old] = FLOOR;
        map->buffer[y1_old] = FLOOR;
        map->buffer[y2_old] = FLOOR;
        map->buffer[y3_old] = FLOOR;
        map->y++;
        map_render_player(map);
    }
}
void player_move_right(map_t *map) {
    if (map->x == SIZE_W - 1) return;

    /* these 2 are the left part of the player */
    uint32_t x_old = square_to_linear(map->y, map->x, SIZE_W);
    uint32_t x1_old = square_to_linear(map->y + 1, map->x, SIZE_W);
    
    /* these 2 are the right part of the player */
    uint32_t x2_old = square_to_linear(map->y, map->x + 1, SIZE_W);
    uint32_t x3_old = square_to_linear(map->y + 1, map->x + 1, SIZE_W);

    uint32_t x_new = x2_old;
    uint32_t x1_new = x3_old;
    uint32_t x2_new = square_to_linear(map->y, map->x + 1 + 1, SIZE_W);
    uint32_t x3_new = square_to_linear(map->y + 1, map->x + 1 + 1, SIZE_W);
    if ((map->buffer[x2_new] == FLOOR) && (map->buffer[x3_new] == FLOOR)) {
        map->buffer[x_old] = FLOOR;
        map->buffer[x1_old] = FLOOR;
        map->buffer[x2_old] = FLOOR;
        map->buffer[x3_old] = FLOOR;
        map->x++;
        map_render_player(map);
    }

}
void player_move_left(map_t *map) {
    if (map->x == 0) return;

    /* these 2 are the left part of the player */
    uint32_t x_old = square_to_linear(map->y, map->x, SIZE_W);
    uint32_t x1_old = square_to_linear(map->y + 1, map->x, SIZE_W);
    
    /* these 2 are the right part of the player */
    uint32_t x2_old = square_to_linear(map->y, map->x + 1, SIZE_W);
    uint32_t x3_old = square_to_linear(map->y + 1, map->x + 1, SIZE_W);

    uint32_t x_new = x2_old;
    uint32_t x1_new = x3_old;
    uint32_t x2_new = square_to_linear(map->y, map->x -1, SIZE_W);
    uint32_t x3_new = square_to_linear(map->y + 1, map->x - 1, SIZE_W);
    if ((map->buffer[x2_new] == FLOOR) && (map->buffer[x3_new] == FLOOR)) {
        map->buffer[x_old] = FLOOR;
        map->buffer[x1_old] = FLOOR;
        map->buffer[x2_old] = FLOOR;
        map->buffer[x3_old] = FLOOR;
        map->x--;
        map_render_player(map);
    }
}




uint32_t enemy_attack(enemy_state_t *est, player_state_t *pst) {
    uint32_t dmg = est->dmg * rand_int(1, 3); /* same logic as player_attack */
    pst->hp -= dmg;
    return dmg;
}

enemy_state_t *enemy_generate() {
    enemy_state_t *est = (enemy_state_t*)malloc(sizeof(enemy_state_t)); /* temporary */
    est->dmg = 5;
    est->hp = 100;
    return est;
}