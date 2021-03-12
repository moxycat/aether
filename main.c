#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include "mapgen.h"
#include "player.h"
#include "battle.h"
#include "global.h"
#include "util.h"
#include "graphics.h"

char fov_map[ROWS][COLS];
int cheat = 0;

char *concat(char *str1, char *str2) {
    char *output = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}

int enemies(int level) {
    return (level % rand_int(5, 10)) + rand_int(1, 5);
}

void console_cursor_hide(HANDLE con) {
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(con, &info);
}

void console_clear(HANDLE console) {
    COORD topLeft  = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void console_set_size(int width, int height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

void draw(HANDLE con, world_t *w) {
    DWORD written;
    char status[COLS + 1];
    char *frame;
    if (cheat > 0) sprintf(status, "HP: %d/%d | DMG: %d | COINS: %d | LVL: %d | ENEMIES: %d | POS: %d %d | EXIT: %d %d ",
        w->player->hp, player_max_hp, w->player->dmg, w->player->coins, w->depth, w->enemy_count, w->player->x, w->player->y, w->exit_x, w->exit_y);
    else sprintf(status, "HP: %d/%d | DMG: %d | COINS: %d | LVL: %d | ENEMIES: %d ", w->player->hp, player_max_hp, w->player->dmg, w->player->coins, w->depth, w->enemy_count);
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
    map_add_coins(w);
    map_add_enemies(w);
    map_add_exit(w);
}

int main(int argc, char **argv) {
    HANDLE con = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(con);
    SetConsoleTitleA("Disciple of Gods");
    SetWindowLongA(GetConsoleWindow(), GWL_STYLE, GetWindowLongA(GetConsoleWindow(), GWL_STYLE) & ~WS_MAXIMIZEBOX);
    SetWindowLongA(GetConsoleWindow(), GWL_STYLE, GetWindowLongA(GetConsoleWindow(), GWL_STYLE) & ~WS_THICKFRAME);
    console_set_size(800, 600);
    console_cursor_hide(con);
    srand(time(0)); /* 0 for testing only */

    world_t *w = (world_t*)malloc(sizeof(world_t));

    int current_level = 1;
    int key = 0x0;
    int last_dir = 0x44;
    int last_status = STATUS_ROAM;

    //w->enemy_count = enemies(current_level);

    w->enemy_count = enemies(current_level);
    w->player = (entity_t*)malloc(sizeof(entity_t));
    
    w->depth = current_level;
    w->player->hp = player_max_hp;
    w->player->dmg = player_init_dmg;
    w->player->coins = 0;

    make_map(w);

    draw(con, w);
    while (key != '\\') {
        /* clear the console on status change */
        if (last_status != w->status) {
            console_clear(con);
            last_status = w->status;
        }

        if (w->status == STATUS_ROAM) {
            if (w->depth != current_level) {
                current_level++;
                w->enemy_count = enemies(current_level);
                make_map(w);
                draw(con, w);
            }
            draw(con, w);
            key = getch();
        
            if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
                move_up(w);
                //draw(con, w);
                last_dir = 0x57;
            }
            else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
                move_down(w);
                //draw(con, w);
                last_dir = 0x53;
            }
            else if ((GetAsyncKeyState(0x41) & 0x8000) != 0) {
                move_left(w);
                //draw(con, w);
                last_dir = 0x41;
            }
            else if ((GetAsyncKeyState(0x44) & 0x8000) != 0) {
                move_right(w);
                //draw(con, w);
                last_dir = 0x44;
            }
            /* break wall */
            else if ((GetAsyncKeyState(0x51) & 0x8000) != 0) {
                break_wall(w, last_dir);
                //draw(con, w);
            }
            /* attack */
            else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) {
                fight_enemy(w);
            }
            /* open menu */
            else if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0) {
                w->status = STATUS_INMENU;
            }
            /* cheat */
            if ((GetAsyncKeyState(VK_OEM_3) & 0x8000) != 0) {
                cheat++;
                cheat %= 3;
                //draw(con, w);
            }
        }
        else if (w->status == STATUS_INFIGHT) {
            battle(con, w->player);
            /* use last_dir to remove the enemy from the map 
            kinda hacky solution */
            switch (last_dir) {
                case 0x57: w->map[w->player->y - 1][w->player->x] = FLOOR; break;
                case 0x53: w->map[w->player->y + 1][w->player->x] = FLOOR; break;
                case 0x41: w->map[w->player->y][w->player->x - 1] = FLOOR; break;
                case 0x44: w->map[w->player->y][w->player->x + 1] = FLOOR; break;
            }
            w->enemy_count--;
            w->status = STATUS_ROAM;
        }
        else if (w->status == STATUS_INMENU) {
            while (w->status == STATUS_INMENU) {
                
            }
        }
        Sleep(50);
    }
    free(w);
    return 0;
}