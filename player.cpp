#include "entity.hpp"
#include "const.hpp"
#include "util.hpp"

int player_dmg_fin(player_state_t *pst){
	return pst -> dmg_base + rand() % pst -> dmg_vary;
}

void player_attack(player_state_t *pst, enemy_state_t *est){
	int dmg_fin = player_dmg_fin(pst);
	est -> hp_curr -= dmg_fin;

	cout << "you attacked for " << dmg_fin << " damage\n\n";
}


