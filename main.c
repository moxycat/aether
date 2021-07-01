#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <MMSystem.h>

#include "mapgen.h"
#include "player.h"
#include "battle.h"
#include "global.h"
#include "util.h"
#include "inv.h"
#include "graphics.h"
#include "audio.h"
#include "smithy.h"
#include "inn.h"

/*
    TODO:
    - add inits for all aspects of an item
    - add player_use
    - add chest interaction
    - add stats display to inventory (based on the usage variable)
    - add ore interaction
    - finally add the town? o_o
    - fix battles so that they don't take over the entire screen
*/

/* vladi you fker why'd you make the town an
    array of strings and not an array of chars?!?!? */
/*make your mum :sunglasses:*/    

int enemies(int level) {
    return (level % rand_int(5, 10)) + rand_int(1, 5);
}

void make_map(world_t *w) {
    map_init(w->map);
    map_iter(w->map, 4);
    spawn_player(w);
    map_add_coins(w);
    map_add_enemies(w);
    map_add_chest(w);
    map_add_ore(w);
    map_add_exit(w);
}

int cheat;

int main(int argc, char **argv) {
    HANDLE con = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(con);
    SetConsoleTitleA("Scourge");
    SetWindowLongA(GetConsoleWindow(), GWL_STYLE, GetWindowLongA(GetConsoleWindow(), GWL_STYLE) & ~WS_MAXIMIZEBOX);
    //SetWindowLongA(GetConsoleWindow(), GWL_STYLE, GetWindowLongA(GetConsoleWindow(), GWL_STYLE) & ~WS_THICKFRAME);
    SetWindowLongA(GetConsoleWindow(), GWL_STYLE, GetWindowLongA(GetConsoleWindow(), GWL_STYLE) & ~WS_VSCROLL);
    console_set_size(800, 600);
    console_cursor_hide(con);
    srand(time(0)); /* 0 for testing only */

    int current_level = 1;
    int key = 0x0;
    int last_dir = 0x44;
    int last_status = STATUS_ROAM;
    int choice = 0;

    /* add the main menu here */
    DWORD written;
    for (int i = 0; i < 35; ++i) {
        WriteConsoleA(con, main_menu_text[i], strlen(main_menu_text[i]), &written, NULL);
    }
    int proceed = 0;
    PlaySound(NULL, NULL, SND_ASYNC);
    PlaySoundA((LPCSTR) "music\\menu.wav", NULL, SND_FILENAME | SND_ASYNC);
    do {
        key = getch();
        switch (key) {
            case '1': proceed = 1; break;
            case '2': exit(0); break;
            default: break;
        }
    } while(!proceed);

    world_t *w = (world_t*)malloc(sizeof(world_t));

    w->enemy_count = enemies(current_level);
    w->player = (entity_t*)malloc(sizeof(entity_t));
    w->player->inv = (inventory_t*)malloc(sizeof(inventory_t));

    w->depth = current_level;
    w->player->hp = player_max_hp;
    w->player->dmg = player_init_dmg;
    w->player->dmg_vary = player_init_dmg_vary;
    w->player->coins = 0;
    w->player->armour = 0;
    w->player->armour_lvl = 0;
    w->player->weapon_lvl = 0;

    cheat = 0;

    int x1 = 0, y1 = 0; /* saves the coordinates to where the player should be spawned in the cave */

    inventory_init(w->player->inv, (int[]){0, 0, 0, 0, 5, 1, 0});
    make_map(w);
    PlaySound(NULL, NULL, SND_ASYNC);
    PlaySoundA((LPCSTR) "music\\depths.wav", NULL, SND_FILENAME | SND_ASYNC); //workaround?

    draw(con, w);
    while (1) {
        /* clear the console on status change */
        if (last_status != w->status) {
            if (w->status != STATUS_INMENU) console_clear(con);
            last_status = w->status;
        }

        

        if (w->status == STATUS_ROAM) {
         
            draw(con, w);
            key = getch();
            if (w->depth != current_level) {
                choice = display_dialogue_box(con, "Do you wish to return to Altgard or proceed further down?\n", (char *[]){"Return to Altgard", "Proceed further down..."}, 2);
                if (choice == 0)
                    w->status = STATUS_INTOWN;
                current_level++;
                w->enemy_count = enemies(current_level);
                make_map(w);
                x1 = w->player->x;
                y1 = w->player->y;
                
                //draw(con, w);
            }

        
            if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
                move_up(w);
                last_dir = 0x57;
            }
            else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
                move_down(w);
                last_dir = 0x53;
            }
            else if ((GetAsyncKeyState(0x41) & 0x8000) != 0) {
                move_left(w);
                last_dir = 0x41;
            }
            else if ((GetAsyncKeyState(0x44) & 0x8000) != 0) {
                move_right(w);
                last_dir = 0x44;
            }
            /* break wall */
            else if ((GetAsyncKeyState(0x51) & 0x8000) != 0) {
                break_wall(w, last_dir);
            }
            /* use */
            else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) {
                //fight_enemy(w);
            }
            /* open menu */
            else if ((GetAsyncKeyState(VK_TAB) & 0x8000) != 0) {
                w->status = STATUS_INMENU;
            }
            /* cheat */
            if ((GetAsyncKeyState(VK_OEM_3) & 0x8000) != 0) {
                cheat++;
                cheat %= 2;
            }

            
        }
        else if (w->status == STATUS_INFIGHT) {
            PlaySound(NULL, NULL, SND_ASYNC);
            PlaySoundA((LPCSTR) "music\\battle.wav", NULL, SND_FILENAME | SND_ASYNC);
            battle(con, w->player, w->player->inv);
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
            PlaySound(NULL, NULL, SND_ASYNC);
            PlaySoundA((LPCSTR) "music\\depths.wav", NULL, SND_FILENAME | SND_ASYNC); //workaround?
        }
        else if (w->status == STATUS_INMENU) {
            mciSendStringA("play sound\\journal.wav", NULL, 0, NULL);
            inventory_draw(con, w->player->inv);
            w->status = STATUS_ROAM;
        }
        else if (w->status == STATUS_INTOWN) {
            w->player->x = 5;
            w->player->y = 12;
            PlaySound(NULL, NULL, SND_ASYNC);
            PlaySoundA((LPCSTR) "music\\town.wav", NULL, SND_FILENAME | SND_ASYNC);
            draw_town(con, w);
            while (1) {
                draw_town(con, w);
                key = getch();
                
                if      ((GetAsyncKeyState(0x57) & 0x8000) != 0) player_town_move_up(w);
                else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) player_town_move_down(w);
                else if ((GetAsyncKeyState(0x41) & 0x8000) != 0) player_town_move_left(w);
                else if ((GetAsyncKeyState(0x44) & 0x8000) != 0) player_town_move_right(w);

                if (player_town_check_cave(w)) {
                    choice = display_dialogue_box(con, "Start another expedition and delve down?\n", (char *[]){"Yes", "No"}, 2);
                    if (choice == 0) break;
                    else if (choice == 1) w->player->y--;
                }

                if (player_town_check_blacksmith(w)) {
                    display_dialogue_box(con, "You entered the blacksmith.\n", (char *[]){"Continue..."}, 1);
                    smithy(con, w->player, w->player->inv);
                    w->player->x = blacksmith_exit[0];
                    w->player->y = blacksmith_exit[1];
                }

                if (player_town_check_church(w)) {
                    display_dialogue_box(con, "You entered the church.\n", (char *[]){"Continue..."}, 1);
                    
                }

                if (player_town_check_inn(w)) {
                    display_dialogue_box(con, "You entered the inn.\n", (char *[]){"Continue..."}, 1);
                    inn_house(con, w);
                    w->player->x = inn_exit[0];
                    w->player->y = inn_exit[1];
                }

                Sleep(50);
                
            }
            w->player->x = x1;
            w->player->y = y1;
            w->status = STATUS_ROAM;
            PlaySound(NULL, NULL, SND_ASYNC);
            PlaySoundA((LPCSTR) "music\\depths.wav", NULL, SND_FILENAME | SND_ASYNC); //workaround?

        }
        Sleep(50);
    }
    free(w);
    return 0;
}