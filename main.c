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
#include "inv.h"
//#include "graphics.h"

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

void console_clear(HANDLE con) {
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(con, &screen);
    FillConsoleOutputCharacterA(con, ' ', screen.dwSize.X * screen.dwSize.Y, (COORD){0, 0}, &written);
    SetConsoleCursorPosition(con, (COORD){0, 0});
}

void console_set_size(int width, int height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

int display_dialogue_box(HANDLE con, char *text, char **opts, int nopts) {
    int len = 0, cur_len = 0, max_len = 0;
    int selected = 0;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    char *buffer = (char*)malloc(CONSOLE_COLS * nopts);
    SetConsoleCursorPosition(con, (COORD){0, 1});
    WriteConsoleA(con, text, strlen(text), &written, NULL);
    GetConsoleScreenBufferInfo(con, &screen);
    max_len = strlen(text);
    for (int i = 0; i < nopts; ++i) {
        len += sprintf(buffer + len, " %s\n", opts[i]);
        cur_len = snprintf(NULL, 0, " %s\n", opts[i]);
        if (cur_len > max_len) max_len = cur_len;
    }
    for (int i = 1; i < nopts + screen.dwCursorPosition.Y; ++i) {
        FillConsoleOutputCharacterA(con, ' ', max_len, (COORD){0, i}, &written);
    }
    SetConsoleCursorPosition(con, (COORD){0, 1});
    WriteConsoleA(con, text, strlen(text), &written, NULL);
    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    

    FillConsoleOutputCharacterA(con, '-', max_len, (COORD){0, nopts + screen.dwCursorPosition.Y}, &written);
    for (int i = 1; i <= nopts + screen.dwCursorPosition.Y; ++i) FillConsoleOutputCharacterA(con, '|', 1, (COORD){max_len, i}, &written);
    FillConsoleOutputCharacterA(con, '+', 1, (COORD){max_len, nopts + screen.dwCursorPosition.Y}, &written);

    FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, screen.dwCursorPosition.Y}, &written);
    while (1) {
        getch();
        FillConsoleOutputCharacterA(con, ' ', 1, (COORD){0, selected + screen.dwCursorPosition.Y}, &written);

        if ((GetAsyncKeyState(0x57) & 0x8000) != 0) selected--;
        else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) selected++;
        else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) break;

        if (selected < 0) selected = 0;
        if (selected > nopts - 1) selected = nopts - 1;
        FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, selected + screen.dwCursorPosition.Y}, &written);
    }

    free(buffer);
    return selected;
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

    int current_level = 1;
    int key = 0x0;
    int last_dir = 0x44;
    int last_status = STATUS_ROAM;

    /* add the main menu here */
    DWORD written;
    for (int i = 0; i < 26; ++i) {
        WriteConsoleA(con, main_menu_text[i], strlen(main_menu_text[i]), &written, NULL);
    }
    int proceed = 0;
    do {
        key = getch();
        switch (key) {
            case '1': proceed = 1; break;
            case '2': exit(0); break;
            default: break;
        }
    } while(!proceed);

    world_t *w = (world_t*)malloc(sizeof(world_t));

    //w->enemy_count = enemies(current_level);

    w->enemy_count = enemies(current_level);
    w->player = (entity_t*)malloc(sizeof(entity_t));
    w->player->inv = (inventory_t*)malloc(sizeof(inventory_t));

    w->depth = current_level;
    w->player->hp = player_max_hp;
    w->player->dmg = player_init_dmg;
    w->player->dmg_vary = player_init_dmg_vary;
    w->player->coins = 0;

    w->player->inv->equipped = -1;
    w->player->inv->inv[0] = 2;
    w->player->inv->inv[1] = 0;
    w->player->inv->inv[2] = 5;
    w->player->inv->inv[3] = 0;
    w->player->inv->inv[4] = 1;

    make_map(w);

    draw(con, w);
    while (1) {
        /* clear the console on status change */
        if (last_status != w->status) {
            if (w->status != STATUS_INMENU) console_clear(con);
            last_status = w->status;
        }

        if (w->status == STATUS_ROAM) {
            if (w->depth != current_level) {
                display_dialogue_box(con, "Do you wish to return to town or\nproceed further down?\n", (char *[]){"Return to town", "Proceed further down"}, 2);


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
            if (w->player->hp <= 0) {
                return - 1;
            }
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
            inventory_draw(con, w->player->inv);
            w->status = STATUS_ROAM;
        }
        Sleep(50);
    }
    free(w);
    return 0;
}