#include "inn.h"

#include <Windows.h>
#include <mmsystem.h>

void inn_house(HANDLE con, world_t *w) {
    int choice;
    mciSendStringA("play sound\\dooropen.wav", NULL, 0, NULL);
    choice = display_dialogue_box(con, "Greetings, traveller. You look beat..If you've coin, we're willing to lend a room for ya.\n", (char *[]){"Rent room (5 coins)", "Leave"}, 2);
    
    draw_town(con, w);
    if (choice == 1) {
        return;
    }
    if (choice == 0) {
        if (w->player->hp >= 90) {
            mciSendStringA("play sound\\doorclos.wav", NULL, 0, NULL);
            display_dialogue_box(con, "On second thought, you feel fresh enough and with enough energy to keep on going...\n", (char *[]){"Leave"}, 1);
            return;
        }

        if (w->player->coins - 5 >= 0) {
            w->player->coins -= 5;
            w->player->hp = player_max_hp;

            mciSendStringA("play sound\\gold.wav", NULL, 0, NULL);
            display_dialogue_box(con, "You wake up, fully sated and well-rested.\nThe inn's doors are wide open for you to leave and continue your ventures..\n", (char *[]){"Continue.."}, 1);
            
            return;
        }
        else {
            display_dialogue_box(con, "Sorry, friend - I don't do charities.\n", (char *[]){"Leave"}, 1);
            return;
        }
    }
}