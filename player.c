#include "player.h"

void spawn_player(world_t *w, int x, int y) {
    w->player_x = x;
    w->player_y = y;
    w->map[w->player_y][w->player_x] = PLAYER;
}

void move_up(world_t *w) {
    int px = w->player_x;
    int py = w->player_y;

    if (py - 1 < 0) return;

    if (w->map[py - 1][px] != WALL) {
        w->player_y--;
        w->map[py][px] = FLOOR;
        w->map[py - 1][px] = PLAYER;
    }
}

void move_down(world_t *w) {
    int px = w->player_x;
    int py = w->player_y;

    if (py + 1 > ROWS - 1) return;

    if (w->map[py + 1][px] != WALL) {
        w->player_y++;
        w->map[py][px] = FLOOR;
        w->map[py + 1][px] = PLAYER;
    }
}

void move_left(world_t *w) {
    int px = w->player_x;
    int py = w->player_y;

    if (px - 1 < 0) return;

    if (w->map[py][px - 1] != WALL) {
        w->player_x--;
        w->map[py][px] = FLOOR;
        w->map[py][px - 1] = PLAYER;
    }
}

void move_right(world_t *w) {
    int px = w->player_x;
    int py = w->player_y;

    if (px + 1 > COLS - 1) return;

    if (w->map[py][px + 1] != WALL) {
        w->player_x++;
        w->map[py][px] = FLOOR;
        w->map[py][px + 1] = PLAYER;
    }
}