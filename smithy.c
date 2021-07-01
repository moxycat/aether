#include "smithy.h"

void upgrade_menu(HANDLE con, entity_t *player, inventory_t *inv, int choice){
    char buffer[CONSOLE_COLS];
    char buffer1[CONSOLE_COLS];
    int arm_p_g = 10 + 3 * player->armour_lvl;
    int arm_p_o = 3 + player->armour_lvl;
    int weap_p_g = 10 + 3 * player->weapon_lvl;
    int weap_p_o = 3 + player->weapon_lvl;

    sprintf(buffer, "Upgrade armour (DEF: %d -> %d) for %d ores and %d gold coins", player->armour, (int)(player->armour * 1.2 + 2), arm_p_o, arm_p_g);
    sprintf(buffer1, "Upgrade weapon (BASE ATK: %d -> %d) for %d ores, %d gold coins", player->dmg, (int)(player->dmg * 1.2 + 3), weap_p_o, weap_p_g);

    choice = display_dialogue_box(con, "I can upgrade your weapons and armour so you can fight off the enemies that plague the cave nearby\n", (char *[]){buffer, buffer1, "Leave"}, 2);
    if(choice == 0) {
        if(player->inv->items[6].quantity < arm_p_o || player->coins < arm_p_g){
            choice = display_dialogue_box(con, "Unfortunately, you don't have enough recources. Go back and fight some more in the cave to gather more.\n", (char *[]){"Go Back", "Leave"}, 2);
            if(choice == 0) upgrade_menu(con, player, inv, choice);
            else return;
        }
        else upgrade_armour(con, player, inv, choice);
    }
    else if(choice == 1) {
        if(player->inv->items[6].quantity < weap_p_o || player->coins < arm_p_g){
            choice = display_dialogue_box(con, "Unfortunately, you don't have enough recources. Go back and fight some more in the cave to gather more.\n", (char *[]){"Go Back", "Leave"}, 2);
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
    choice = display_dialogue_box(con, "Congratulations, your weapon has been improved! You should now be able to fight the stronger monsters in the cave!\n", (char *[]){"Go Back", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}

void upgrade_armour(HANDLE con, entity_t *player, inventory_t *inv, int choice){
    inv->items[6].quantity -= 3 + 2*player->armour_lvl;
    player->coins -= 10 + 2.5 * player->armour_lvl;
    player->armour_lvl++;
    player->armour += (int)(0.5 * player->armour);
    choice = display_dialogue_box(con, "Congratulations, your armour has been improved! You should now be able to fight the stronger monsters in the cave!\n", (char *[]){"Go Back", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}

void smithy(HANDLE con, entity_t *player, inventory_t *inv){
    int choice = display_dialogue_box(con, "Welcome to my smithy, adventurer, I hope I can help you.\n", (char *[]) {"Continue...", "Leave"}, 2);
    if(choice == 0) upgrade_menu(con, player, inv, choice);
    else return;
}