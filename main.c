#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "mapgen.h"
#include "player.h"
#include "global.h"
#include "util.h"

char *concat(char *str1, char *str2) {
    char *output = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}

void print_at(HANDLE con, int x, int y, char c) {
    DWORD written;
    SetConsoleCursorPosition(con, (COORD){x, y});
    WriteConsoleOutputCharacterA(con, c, 1, (COORD){x, y}, &written);
}

void console_cursor_hide(HANDLE con) {
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(con, &info);
}

void console_clear() {
    DWORD written;
    WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), " ", COLS * ROWS, (COORD){0, 0}, &written);
}

void console_set_size(int width, int height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

char fov_map[ROWS][COLS];
int cheat = 0;
void draw(HANDLE con, world_t *w) {
    DWORD written;
    char status[COLS + 1];
    char *frame;
    if (cheat > 0) sprintf(status, "HP: %d/%d | DMG: %d | LVL: %d | POS: %d %d | EXIT: %d %d ",
        w->player->hp, player_max_hp, w->player->dmg, w->depth, w->player->x, w->player->y, w->exit_x, w->exit_y);
    else sprintf(status, "HP: %d/%d | DMG: %d | LVL: %d ", w->player->hp, player_max_hp, w->player->dmg, w->depth);
    for (int i = strlen(status); i < COLS + 1; ++i) {
        status[i] = '=';
    }
    status[COLS] = '\0';
    if (cheat != 2) {
        apply_fov(w, fov_map, 5, 3);
        frame = concat(status, fov_map);
    }
    else frame = concat(status, w->map);
    WriteConsoleOutputCharacterA(con, frame, (ROWS + 1) * COLS, (COORD){0, 0}, &written);
}

void make_map(world_t *w) {
    map_init(w->map);
    map_iter(w->map, 4);
    spawn_player(w);
    map_add_exit(w);
}

int main(int argc, char **argv) {
    HANDLE con = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(con);
    SetConsoleTitleA("Aether Realm");
    console_set_size(800, 600);
    console_cursor_hide(con);
    srand(time(0)); /* 0 for testing only */

    world_t *w = (world_t*)malloc(sizeof(world_t));
    w->player = (entity_t*)malloc(sizeof(entity_t));
    w->enemies = (entity_t**)malloc(sizeof(entity_t) * 3);

    int current_level = 1;
    int key = 0x0;
    int last_dir = 0x44;
    
    w->depth = current_level;
    w->player->hp = player_max_hp;
    w->player->dmg = player_init_dmg;

    make_map(w);

    draw(con, w);
    while (1) {
        key = getch();

        /* level change */
        if (w->depth != current_level) {
            current_level++;
            make_map(w);
            draw(con, w);
        }
        if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
            move_up(w);
            draw(con, w);
            last_dir = 0x57;
        }
        else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
            move_down(w);
            draw(con, w);
            last_dir = 0x53;
        }
        else if ((GetAsyncKeyState(0x41) & 0x8000) != 0) {
            move_left(w);
            draw(con, w);
            last_dir = 0x41;
        }
        else if ((GetAsyncKeyState(0x44) & 0x8000) != 0) {
            move_right(w);
            draw(con, w);
            last_dir = 0x44;
        }
        /* break wall */
        else if ((GetAsyncKeyState(0x51) & 0x8000) != 0) {
            break_wall(w, last_dir);
            draw(con, w);
        }
        /* attack */
        else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) {

        }
        /* i literally cannot pass a single level of this game */
        else if ((GetAsyncKeyState(VK_OEM_3) & 0x8000) != 0) {
            cheat++;
            cheat %= 3;
        }
        Sleep(50);
    }
}