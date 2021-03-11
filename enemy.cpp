#include "entity.hpp"
#include "util.hpp"
#include "const.hpp"

int enemy_dmg_fin(enemy_state_t *est){
	return est -> dmg_base + rand() % est -> dmg_vary;
}

void enemy_attack(player_state_t *pst, enemy_state_t *est){
	int dmg_fin = enemy_dmg_fin(est); 
		
	if(pst -> defending == true){
		dmg_fin /= 2;
		pst -> defending = false;
	}

	dmg_fin -= pst -> defence;		
	pst -> hp_curr -= dmg_fin;	

	cout << "the monster attacks you for " << dmg_fin << " damage. oof\n\n";
}