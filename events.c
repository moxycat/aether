#include "events.h"

void event_battle(player_state_t *pst, enemy_state_t *est) {
    int player_won = 0;
    uint32_t dmg;

    printf("player hp: %d\nenemy hp: %d\n", pst->hp, est->hp);
    getchar();

    while (1) {
        //printf("player is attacking\n");
        dmg = player_attack(pst, est);
        printf("enemy hit for %d hp\n", dmg);
        if (est->hp <= 0) {
            player_won = 1;
            break;
        }
        //printf("enemy is attacking\n");
        dmg = enemy_attack(est, pst);
        printf("player hit for %d hp\n", dmg);
        if (pst->hp <= 0) break;
        printf("player hp: %d\nenemy hp: %d\n", pst->hp, est->hp);
        getchar();
    }
    if (player_won) {
        printf("big dub\n");
    }
    else {
        printf("big l\n");
    }
    return;
}

void event_checkpoint(player_state_t *pst) {
    pst->hp = 100; /* fix later */
}