#include "player.h"

void spawn_player(world_t *w) {
    int x, y;

    do {
        x = rand_int(1, COLS - 1);
        y = rand_int(1, ROWS - 1);
    } while (w->map[y][x] == WALL);
    w->player->x = x;
    w->player->y = y;
    w->map[w->player->y][w->player->x] = PLAYER;
}

void move_up(world_t *w) {
    int px = w->player->x;
    int py = w->player->y;

    if (py - 1 < 0) return;

    if ((w->map[py - 1][px] != WALL) && (w->map[py - 1][px] != PB_WALL)) {
        if (w->map[py - 1][px] == EXIT) w->depth++;
        w->player->y--;
        w->map[py][px] = FLOOR;
        w->map[py - 1][px] = PLAYER;
    }
}

void move_down(world_t *w) {
    int px = w->player->x;
    int py = w->player->y;

    if (py + 1 > ROWS - 1) return;

    if ((w->map[py + 1][px] != WALL) && (w->map[py + 1][px] != PB_WALL)) {
        if (w->map[py + 1][px] == EXIT) w->depth++;
        w->player->y++;
        w->map[py][px] = FLOOR;
        w->map[py + 1][px] = PLAYER;
    }
}

void move_left(world_t *w) {
    int px = w->player->x;
    int py = w->player->y;

    if (px - 1 < 0) return;

    if ((w->map[py][px - 1] != WALL) && (w->map[py][px - 1] != PB_WALL)) {
        if (w->map[py][px - 1] == EXIT) w->depth++;
        w->player->x--;
        w->map[py][px] = FLOOR;
        w->map[py][px - 1] = PLAYER;
    }
}

void move_right(world_t *w) {
    int px = w->player->x;
    int py = w->player->y;

    if (px + 1 > COLS - 1) return;

    if ((w->map[py][px + 1] != WALL) && (w->map[py][px + 1] != PB_WALL)) {
        if (w->map[py][px + 1] == EXIT) w->depth++;
        w->player->x++;
        w->map[py][px] = FLOOR;
        w->map[py][px + 1] = PLAYER;
    }
}

void break_wall(world_t *w, int dir) {
    switch (dir) {
        case 0x57:
            if (w->map[w->player->y - 1][w->player->x] == WALL) {
                w->map[w->player->y - 1][w->player->x] = PB_WALL;
            }
            else if (w->map[w->player->y - 1][w->player->x] == PB_WALL) {
                w->map[w->player->y - 1][w->player->x] = FLOOR;
            }
            break;
        case 0x53:
            if (w->map[w->player->y + 1][w->player->x] == WALL) {
                w->map[w->player->y + 1][w->player->x] = PB_WALL;
            }
            else if (w->map[w->player->y + 1][w->player->x] == PB_WALL) {
                w->map[w->player->y + 1][w->player->x] = FLOOR;
            }
            break;
        case 0x41:
            if (w->map[w->player->y][w->player->x - 1] == WALL) {
                w->map[w->player->y][w->player->x - 1] = PB_WALL;
            }
            else if (w->map[w->player->y][w->player->x - 1] == PB_WALL) {
                w->map[w->player->y][w->player->x - 1] = FLOOR;
            }
            break;
        case 0x44:
            if (w->map[w->player->y][w->player->x + 1] == WALL) {
                w->map[w->player->y][w->player->x + 1] = PB_WALL;
            }
            else if (w->map[w->player->y][w->player->x + 1] == PB_WALL) {
                w->map[w->player->y][w->player->x + 1] = FLOOR;
            }
            break;
    }
}