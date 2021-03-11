#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include "battle.hpp"
#include "entity.hpp"
#include "util.hpp"
#include "const.hpp"
using namespace std;

int main(){
	enemy_state_t est;
	player_state_t pst;
	player_hp_max = 1000;
	pst.hp_curr = 1000;
	pst.dmg_base = 100;
	pst.dmg_vary = 10;
	pst.defence = 20;
	player_name = "a";
	enemy_name = "monster";
	enemy_desc = "im not a front end programmer idk";
	enemy_hp_max = 400;
	est.hp_curr = 400;
	est.dmg_base = 70;
	est.dmg_vary = 7;

	battle(&pst, &est);
}
