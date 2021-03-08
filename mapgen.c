#include "mapgen.h"

void map_init(char map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (rand_int(1, 100) < INITIAL_PROBABILITY) {
                map[i][j] = WALL;
            }
            else map[i][j] = FLOOR;
        }
    }
}

int map_tile_neighbours(char map[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int neighbour_x = x + i;
            int neighbour_y = y + j;
            if (i == 0 && j == 0) continue;
            if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x > COLS - 1 || neighbour_y > ROWS - 1) count++;
            if (map[neighbour_y][neighbour_x] == WALL) count++;
        }
    }
    return count;
}

void map_step(char map[ROWS][COLS]) {
    int newmap[ROWS][COLS];
    int n;

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            n = map_tile_neighbours(map, x, y);
            if (map[y][x] == WALL) {
                if (n >= STAY_WALL_LIMIT) newmap[y][x] = WALL;
                //if (n <= 3) newmap[y][x] = PB_WALL; /* TEST ONLY */
                else newmap[y][x] = FLOOR;
            }
            else {
                if (n >= BECOME_WALL_LIMIT) newmap[y][x] = WALL;
                else newmap[y][x] = FLOOR;
            }
            if (y == 0 || y == ROWS - 1) newmap[y][x] = WALL;
            if (x == 0 || x == COLS - 1) newmap[y][x] = WALL;
        }
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            map[i][j] = newmap[i][j];
        }
    }
}

void map_iter(char map[ROWS][COLS], int n) {
    for (int i = 0; i < n; ++i) {
        map_step(map);
    }
}

void map_add_exit(world_t *w) {
    w->exit_x = -1;
    w->exit_y = -1;
    do {
        for (int y = 0; y < ROWS; ++y) {
            for (int x = 0; x < COLS; ++x) {
                if (5 >= rand_int(1, ROWS * COLS)) {
                    if (w->map[y][x] == FLOOR) {
                        w->map[y][x] = EXIT;
                        w->exit_x = x;
                        w->exit_y = y;
                        return;
                    }
                }
            }
        }
    } while ((w->exit_x == -1) && (w->exit_y == -1));
}

void apply_fov(world_t *w, char map[ROWS][COLS], int fov_x, int fov_y) {
    int py = w->player->y;
    int px = w->player->x;

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if ((abs(y - py) <= fov_y) && (abs(x - px) <= fov_x)) map[y][x] = w->map[y][x];
            else map[y][x] = ' ';
        }
    }
    //return map;
}