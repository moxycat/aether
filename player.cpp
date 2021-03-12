#include "entity.hpp"
#include "const.hpp"
#include "util.hpp"
#include "audio.hpp"
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

int player_dmg_fin(player_state_t *pst){
	return pst -> dmg_base + rand() % pst -> dmg_vary;
}

void player_attack(player_state_t *pst, enemy_state_t *est){
	int dmg_fin = player_dmg_fin(pst);
	est -> hp_curr -= dmg_fin;

	
	mciSendStringA(concat("play sound\\", sounds[13]), NULL, 0, NULL);
	cout << "*You swing your weapon and hit the enemy for " << dmg_fin << " damage.\n\n"; 
	Sleep(1400);
}


