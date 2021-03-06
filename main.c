#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#include "mapgen.h"
#include "player.h"
#include "util.h"

/*
    prints a string at a given coordinate in the console
    (unused)
*/
void print_at(HANDLE con, int x, int y, char c) {
    DWORD written;
    SetConsoleCursorPosition(con, (COORD){x, y});
    WriteConsoleOutputCharacterA(con, c, 1, (COORD){x, y}, &written);
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
    char *status = "HP: 100/100 ";
    char *ws = (char*)malloc(COLS - strlen(status) + 1);
    for (int i = 0; i < COLS - strlen(status); ++i) {
        ws[i] = '=';
    }
    ws[COLS - strlen(status)] = '\0';
    status = concat(status, ws);
    status = concat(status, map);
    WriteConsoleOutputCharacterA(con, status, (ROWS + 1) * COLS, (COORD){0, 0}, &written);
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