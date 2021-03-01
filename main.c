#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "events.h"
#include "io.h"

int main(int argc, char **argv) {
    player_state_t pst = {100, 5};
    enemy_state_t est;

    srand(time(0));
    console_clear();
    /* game loop */
    while (1) {
        est = *enemy_generate();
        event_battle(&pst, &est);
        event_checkpoint(&pst);
    }
}