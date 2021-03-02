#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "events.h"
#include "map.h"
#include "console.h"

int main(int argc, char **argv) {
    player_state_t pst = {100, 5};
    enemy_state_t est;
    srand(time(0));
    SetConsoleTitleA("lsrpg");
    console_clear();
    console_set_size(640, 480);
    console_t con = console_init(640, 480, SIZE_W, SIZE_H);


    map_t map = map_init();

    /* game loop */
    while (1) {
        /* W */
        if ((GetAsyncKeyState(0x57) & 0x8000 != 0)) player_move_up(&map);
        /* S */
        else if ((GetAsyncKeyState(0x53) & 0x8000 != 0)) player_move_down(&map);
        /* A */
        else if ((GetAsyncKeyState(0x41) & 0x8000 != 0)) player_move_left(&map);
        /* D */
        else if ((GetAsyncKeyState(0x44) & 0x8000 != 0)) player_move_right(&map);
        else if ((GetAsyncKeyState(VK_SPACE) & 0x8000 != 0)) {

        }

        console_write_buffer(&con, map.buffer, map.width, map.height);
        //est = *enemy_generate();
        //event_battle(&pst, &est);
        //event_checkpoint(&pst);
    }
}