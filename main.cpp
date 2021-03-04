#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include "battle.hpp"
#include "entity.hpp"
#include "util.hpp"
using namespace std;

int main(){
	enemy_state_t est;
	player_state_t pst;
	pst.hp_max = 1000;
	pst.hp_curr = 1000;
	pst.dmg_base = 100;
	pst.defence = 20;
	pst.lvl = 1;
	pst.name = "a";
	est.name = "monster";
	est.desc = "im not a front end programmer idk";
	est.hp_max = 400;
	est.hp_curr = 400;
	est.dmg_base = 70;

	battle(&pst, &est);
}
