#include "smithy.h"

#include <Windows.h>
#include <mmsystem.h>

void upgrade_menu(HANDLE con, entity_t *player, inventory_t *inv, int choice){
    char buffer[CONSOLE_COLS];
    char buffer1[CONSOLE_COLS];
    int arm_p_g = 10 + 3 * player->armour_lvl;
    int arm_p_o = 3 + player->armour_lvl;
    int weap_p_g = 10 + 3 * player->weapon_lvl;
    int weap_p_o = 3 + player->weapon_lvl;

    sprintf(buffer, "Upgrade armour (DEF: %d -> %d) for %d ores and %d gold coins", player->armour, (int)(player->armour * 1.2 + 2), arm_p_o, arm_p_g);
    sprintf(buffer1, "Upgrade weapon (BASE ATK: %d -> %d) for %d ores, %d gold coins", player->dmg, (int)(player->dmg * 1.2 + 3), weap_p_o, weap_p_g);

    choice = display_dialogue_box(con, "So - what will it be? A sharp blade or a hard plate?\n", (char *[]){buffer, buffer1, "Leave"}, 2);
    if(choice == 0) {
        if(player->inv->items[6].quantity < arm_p_o || player->coins < arm_p_g){
            choice = display_dialogue_box(con, "You know blacksmiths need metal t' work with. Come back once you have some and I'll gladly help.\n", (char *[]){"Go Back", "Leave"}, 2);
            if(choice == 0) upgrade_menu(con, player, inv, choice);
            else return;
        }
        else upgrade_armour(con, player, inv, choice);
    }
    else if(choice == 1) {
        if(player->inv->items[6].quantity < weap_p_o || player->coins < arm_p_g){
            choice = display_dialogue_box(con, "You know blacksmiths need metal t' work with. Come back once you have some and I'll gladly help.\n", (char *[]){"Go Back", "Leave"}, 2);
            if(choice == 0) upgrade_menu(con, player, inv, choice);
            else return;
        }
        else upgrade_weapon(con, player, inv, choice);
    }
}

void upgrade_weapon(HANDLE con, entity_t *player, inventory_t *inv, int choice){
    inv->items[6].quantity -= 3 + 2*player->weapon_lvl;
    player->coins -= 10 + 2.5 * player->weapon_lvl;
    player->weapon_lvl++;
    player->dmg += (int)(0.4 * player->dmg);
    player->dmg_vary++;
    mciSendStringA("play sound\\repair.wav", NULL, 0, NULL);
    choice = display_dialogue_box(con, "There ya go..all sharpened and ready to cleave!\n", (char *[]){"Go Back", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}

void upgrade_armour(HANDLE con, entity_t *player, inventory_t *inv, int choice){
    inv->items[6].quantity -= 3 + 2*player->armour_lvl;
    player->coins -= 10 + 2.5 * player->armour_lvl;
    player->armour_lvl++;
    player->armour += (int)(0.5 * player->armour);
    mciSendStringA("play sound\\repair.wav", NULL, 0, NULL);
    choice = display_dialogue_box(con, "There we go - the sturdiest in town, and it'll only get better!\n", (char *[]){"Go Back", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}

void smithy(HANDLE con, entity_t *player, inventory_t *inv){
    int choice = display_dialogue_box(con, "Welcome to my smithy, traveller, I hope I can be of service to ya.\n", (char *[]) {"Continue...", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}