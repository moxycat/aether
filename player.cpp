#include "entity.hpp"
#include "util.hpp"

void player_attack(player_state_t *pst, enemy_state_t *est){

	pst -> dmg_fin = pst -> dmg_base * (1 + (rand() % 21) / 100);
	est -> hp_curr -= pst -> dmg_fin;
}


