#include <iostream>
#include <stdio.h>
#include <string>
#include "battle.hpp"
#include "entity.hpp"
#include "util.hpp"
using namespace std;


void battle(player_state_t *pst, enemy_state_t *est){	
	cout << "The battle starts";
	while(1){	
		player_turn(pst, est);
		if(est -> hp_curr <= 0){
			victory(pst, est);
			break;
		}
		else if(pst -> escape == true){
			pst -> escape = false;
			break;
		}

		enemy_turn(pst, est);
		if(pst -> hp_curr <= 0){
			defeat(pst, est);
			break;
		}
	}
}

void victory(player_state_t *pst, enemy_state_t *est){
	cout << "condragulations you won\n";
}

void defeat(player_state_t *pst, enemy_state_t *est){
	cout << "oh no you died. uf.";
}

void enemy_turn(player_state_t *pst, enemy_state_t *est){
	cout << "its the enemy's turn\n";
	enemy_attack(pst, est);
	cout << "the enemy attacks for " << est -> dmg_fin << " damage. uf.\n\n";
}
	
void player_turn(player_state_t *pst, enemy_state_t *est){
	cout << "It's your turn. What will you do?\t\t\tHP: " << pst -> hp_curr << "/" << pst -> hp_max << " ATK: " << pst -> dmg_base << "\n1.Attack\n2.Defend\n3.Run\n4.Info\n";
	do{
		cin >> pst -> choice;
		if(pst -> choice < 1 || pst -> choice > 4)
			cout << "Invalid choice. Choose between 1 and 4.\n\n";
	}while(pst -> choice < 1 || pst -> choice > 4);
	
	switch(pst -> choice){
		case 1: 
			player_attack(pst, est);
			cout << "You attack the monster for " << pst -> dmg_fin << " damage. uf.\n\n";
			break;
			
		case 2:
			cout << "You stand strong and will take less damage next turn.\n\n";
			pst -> defending = true;
			break;
			
		case 3:
			if(rand() % 2 == 0){
				cout << "you ran away succesfully\n\n";
			}
			else{
				enemy_attack(pst, est);
				cout << "you ran away, but the monster hit you one last time for " << est -> dmg_fin << " damage.\n\n";
				}
			pst -> escape = true;	
			break;
			
		case 4:	
			cout << "\n" << est -> name << "\nattack: " << est -> dmg_base << "\nhp: " << est -> hp_curr << "\n" << est -> desc << "\n\n"; break;			
	}
	
}





