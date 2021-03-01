#include "entity.h"

uint32_t player_attack(player_state_t *pst, enemy_state_t *est) {
    uint32_t dmg = pst->dmg * rand_int(1, 3); /* multiplier between 1 and 2 */
    est->hp -= dmg;
    return dmg;
}

void player_defend(player_state_t *pst, enemy_state_t *est) {
    /* implement */
}

uint32_t enemy_attack(enemy_state_t *est, player_state_t *pst) {
    uint32_t dmg = est->dmg * rand_int(1, 3); /* same logic as player_attack */
    pst->hp -= dmg;
    return dmg;
}

enemy_state_t *enemy_generate() {
    enemy_state_t *est = (enemy_state_t*)malloc(sizeof(enemy_state_t)); /* temporary */
    est->dmg = 5;
    est->hp = 100;
    return est;
}