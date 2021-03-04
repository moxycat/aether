#include "entity.hpp"
#include "util.hpp"

void enemy_attack(player_state_t *pst, enemy_state_t *est){
	est -> dmg_fin = est -> dmg_base; 
		
	if(pst -> defending == true){
		est -> dmg_fin /= 2;
		pst -> defending = false;
	}

	est -> dmg_fin -= pst -> defence;		
	pst -> hp_curr -= est -> dmg_fin;	
}