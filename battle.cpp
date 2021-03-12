#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <MMSystem.h>
#include "battle.hpp"
#include "entity.hpp"
#include "util.hpp"
#include "const.hpp"
#include "audio.hpp"

using namespace std;


void battle(player_state_t *pst, enemy_state_t *est){	
	cout << "You are under attack!!!\n\n";
	mciSendStringA(concat("play sound\\", sounds[1]), NULL, 0, NULL);
	PlaySoundA((concat("music\\", tracks[0])), NULL, SND_ASYNC | SND_LOOP);
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
	mciSendStringA(concat("play sound\\", sounds[7]), NULL, 0, NULL);
	Sleep(2000);
	mciSendStringA(concat("play sound\\", sounds[3]), NULL, 0, NULL);
	PlaySound(NULL, NULL, SND_ASYNC);
	cout << "As the fiend falls, your courage stands tall. You've won the encounter.\n"; //could list loot as well when implemented
	Sleep(1200);
}

void defeat(player_state_t *pst, enemy_state_t *est){
	mciSendStringA(concat("play sound\\", sounds[0]), NULL, 0, NULL);
	PlaySound(NULL, NULL, SND_ASYNC);
	cout << "Before you even get to reflect on your life, you are struck down viciously by your enemy. Humanity is now doomed to fall...\n";
	Sleep(3000);
}

void enemy_turn(player_state_t *pst, enemy_state_t *est){
	cout << "---ENEMY TURN---\n";
	enemy_attack(pst, est);
}
	
void player_turn(player_state_t *pst, enemy_state_t *est){
	cout << "---YOUR TURN---\t\t\tHP: " << pst -> hp_curr << "/" << player_hp_max << " ATK: " << pst -> dmg_base << "\n1.Attack\n2.Defend\n3.Run\n4.Info\n";
	do{
		choice = getch();
		if(choice < '1' || choice > '4')
			cout << "---INVALID CHOICE: Choose a number between 1-4---\n\n";
	}while(choice < '1' || choice > '4');
	
	switch(choice){
		case '1': 
			player_attack(pst, est);
			break;
			
		case '2':
			mciSendStringA(concat("play sound\\", sounds[10]), NULL, 0, NULL);
			cout << "You take a defensive stance, expecting your enemy's vicious attack, bolstering your defense for the next turn.\n\n";
			pst -> defending = true;
			Sleep(3000);
			break;
			
		case '3':
			if(rand() % 2 == 0){
				mciSendStringA(concat("play sound\\", sounds[11]), NULL, 0, NULL);
				cout << "You have decided your chances of winning have faltered, and cowardly sprint away from your adversaries...\n\n";
				Sleep(3000);
			}
			else{
				mciSendStringA(concat("play sound\\", sounds[11]), NULL, 0, NULL);
				cout << "You have decided your chances of winning have faltered, and cowardly sprint away from your adversaries...\n";
				cout << "...but even that you do sloppily. The enemy could hit you one last time...\n";
				Sleep(3000);
				enemy_attack(pst, est);
				}
			pst -> escape = true;	
			break;
			
		case '4':	
			mciSendStringA(concat("play sound\\", sounds[12]), NULL, 0, NULL);
			cout << "\n" << enemy_name << "\nAttack: " << est -> dmg_base << "\nHP: " << est -> hp_curr << "/" << enemy_hp_max << "\n" << enemy_desc << "\n\n"; 
			Sleep(1200);			

			break;
	}
	
}





