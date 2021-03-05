#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ROWS 35
#define COLS 98

#define INITIAL_PROBABILITY 45
#define STAY_WALL_LIMIT 4
#define BECOME_WALL_LIMIT 5

#define WALL '#'
#define FLOOR '.'
#define PLAYER '@'
#define CHEST 'T'

/*
    contains info about the world, i.e. the map, player position
    depth should be added at some point as well
*/
typedef struct _world {
    char map[ROWS][COLS];
    int player_x;
    int player_y;
} world_t;

/*
    generate a random integer within a closed interval
    [min, max]
*/
int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

/*
    initial map creation
    each cell has a 45% probability of being a wall
    otherwise it's floor
*/
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

/*
    counts the number of walls around a given cell
    X X X
    X O X
    X X X
    counts how many of the Xs are walls
*/
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

/*
    gives the next iteration of the map after applying the rules once
*/
void map_step(char map[ROWS][COLS]) {
    int newmap[ROWS][COLS];
    int n;

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            n = map_tile_neighbours(map, x, y);
            if (map[y][x] == WALL) {
                if (n >= STAY_WALL_LIMIT) newmap[y][x] = WALL;
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

/* 
    applies map_step n times
*/
void map_iter(char map[ROWS][COLS], int n) {
    for (int i = 0; i < n; ++i) {
        map_step(map);
    }
}

/*
    prints a character at a given coordinate in the console
    (unused)
*/
void print_at(HANDLE con, int x, int y, char c) {
    SetConsoleCursorPosition(con, (COORD){x, y});
    putchar(c);
}

/*
    clears the console buffer
    (unused)
*/
void console_clear() {
    DWORD written;
    WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), " ", COLS * ROWS, (COORD){0, 0}, &written);
}

/*
    sets the console's window's size
    (in pixels, not characters)
*/
void console_set_size(int width, int height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

/*
    writes the map array directly to the console buffer
*/
void print_map(HANDLE con, char map[ROWS][COLS]) {
    DWORD written;
    WriteConsoleOutputCharacterA(con, map, ROWS * COLS, (COORD){0, 0}, &written);
}

/*
    places the player at a given location on the map
    this should be reworked such that it spawns the player
    in a spot that is not enclosed
*/
void spawn_player(world_t *w, int x, int y) {
    w->player_x = x;
    w->player_y = y;
    w->map[w->player_y][w->player_x] = PLAYER;
}

/*
    moves the player up one cell
*/
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

/*
    moves the player down one cell
*/
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

/*
    moves the player one cell to the left
*/
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

/*
    moves the player one cell to the right
*/
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

/*
    the main function, of course
*/
int main(int argc, char **argv) {
    /* setting up the console */
    /* create a console buffer */
    HANDLE con = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    /* assign said console buffer to our console */
    SetConsoleActiveScreenBuffer(con);
    /* set the window size to 800x600 */
    console_set_size(800, 600);
    /* seed the prng */
    srand(0); /* 0 for testing only */

    /* allocate memory for a world structure */
    world_t *w = (world_t*)malloc(sizeof(world_t));

    /* initialise the map within the world we just allocated */
    map_init(w->map);
    /* iterate the map a bit so as to smooth it out */
    map_iter(w->map, 4);
    /* spawn the player */
    spawn_player(w, 23, 5);
    /*
        since the graphics update only when a recognised key is pressed
        print the map once before anything has happend
    */
    print_map(con, w->map);

    /*
        the game loop
        random encounters will be handled here as well
    */
    while (1) {
        /* check is w is pressed */
        if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
            move_up(w);
            print_map(con, w->map);
        }
        /* check if s is pressed */
        else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
            move_down(w);
            print_map(con, w->map);
        }
        /* check if a is pressed */
        else if ((GetAsyncKeyState(0x41) & 0x8000) != 0) {
            move_left(w);
            print_map(con, w->map);
        }
        /* check if d is pressed */
        else if ((GetAsyncKeyState(0x44) & 0x8000) != 0) {
            move_right(w);
            print_map(con, w->map);
        }
        /* wait 50 ms so as to not overload the cpu */
        Sleep(50);
    }
}