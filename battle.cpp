#include <iostream>
#include <stdio.h>
#include <string>
#include "battle.hpp"
#include "entity.hpp"
#include "util.hpp"
#include "const.hpp"
using namespace std;


void battle(player_state_t *pst, enemy_state_t *est){	
	cout << "The battle starts\n\n";
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
	cout << "oh no you died. uf.\n";
}

void enemy_turn(player_state_t *pst, enemy_state_t *est){
	cout << "its the enemy's turn\n";
	enemy_attack(pst, est);
}
	
void player_turn(player_state_t *pst, enemy_state_t *est){
	cout << "It's your turn. What will you do?\t\t\tHP: " << pst -> hp_curr << "/" << player_hp_max << " ATK: " << pst -> dmg_base << "\n1.Attack\n2.Defend\n3.Run\n4.Info\n";
	do{
		choice = getch();
		if(choice < '1' || choice > '4')
			cout << "Invalid choice. Choose between 1 and 4.\n\n";
	}while(choice < '1' || choice > '4');
	
	switch(choice){
		case '1': 
			player_attack(pst, est);
			break;
			
		case '2':
			cout << "You stand strong and will take less damage next turn.\n\n";
			pst -> defending = true;
			break;
			
		case '3':
			if(rand() % 2 == 0){
				cout << "you ran away succesfully\n\n";
			}
			else{
				enemy_attack(pst, est);
				}
			pst -> escape = true;	
			break;
			
		case '4':	
			cout << "\n" << enemy_name << "\nattack: " << est -> dmg_base << "\nhp: " << est -> hp_curr << "/" << enemy_hp_max << "\n" << enemy_desc << "\n\n"; break;			
	}
	
}





