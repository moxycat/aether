#include <Windows.h>
#include <mmsystem.h>

#include "battle.h"
#include "audio.h"


entity_t *make_enemy() {
    entity_t *e = (entity_t*)malloc(sizeof(entity_t));
    e->dmg = 3 + rand_int(0, 3);
    e->dmg_vary = 3;
    e->max_hp = 20 + rand_int(0, 10);
    e->hp = e->max_hp;
    e->coins = rand_int(5, 10);
    return e;
}

int enemy_turn(HANDLE con, entity_t *player, entity_t *enemy){
    int dmg_final = enemy->dmg + rand_int(0, enemy->dmg_vary) - player->armour;
    if(player->defending){
        dmg_final /= 2;
        player->defending = 0;
    }
    if(player->armour > dmg_final)
        dmg_final = 0;
    player->hp -= dmg_final;
    return dmg_final;
}

void victory(HANDLE con, entity_t *player, entity_t *enemy, inventory_t *inv){
    DWORD written;
	mciSendStringA("play sound\\zombied.wav", NULL, 0, NULL);
    Sleep(2000);
    player->coins += enemy->coins;
	WriteConsoleA(con, "As the fiend falls, you stand stalwart. You've won the encounter!\n\n", 67, &written, NULL); //could list loot as well when implemented
    mciSendStringA("play sound\\win.wav", NULL, 0, NULL);
    drops(con, inv);
    Sleep(6000);
}

void defeat(HANDLE con){
    DWORD written;
	mciSendStringA("play sound\\playerd.wav", NULL, 0, NULL);
	WriteConsoleA(con, "Before you even get to reflect on your life, you are struck down viciously by your enemy. The townsfolk shall weave tales of your bravery...\n\n", 142, &written, NULL);
	Sleep(6000);
}

void player_turn(HANDLE con, entity_t *player, entity_t *enemy){
    DWORD written;
    char buffer[CONSOLE_COLS];

    int opt;
    player->escaped = 0;
    int p_dmg;

    sprintf(buffer, "\nPlayer: HP: %d/%d ATK: %d-%d\tEnemy: HP: %d/%d ATK: %d-%d\n", player->hp, player_max_hp, player->dmg, player->dmg + player->dmg_vary, enemy->hp, enemy->max_hp, enemy->dmg, enemy->dmg + enemy->dmg_vary);
    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    WriteConsoleA(con, "1.Attack\n2.Defend\n3.Run\n4.Item\n", 31, &written, NULL);

    do {
        opt = getch();
        if (opt < '1' || opt > '4') WriteConsoleA(con, "That is not a valid action.\n", 29, &written, NULL);
    } while (opt < '1' || opt > '4');

    switch(opt){
        case '1':
            if(rand_int(1, 7) == 1){
                WriteConsoleA(con, "You swing your weapon at the enemy, but they dodged out of the way quickly...\n", 78, &written, NULL);
                mciSendStringA("play sound\\miss.wav", NULL, 0, NULL);
                Sleep(1400);
            }
            else{    
                p_dmg = player_attack(player, enemy);
                mciSendStringA("play sound\\basicattack.wav", NULL, 0, NULL);
                sprintf(buffer, "You swing your weapon and dealt %d damage to the enemy.\n", p_dmg);
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
                Sleep(1400);
            }
            break;

        case '2':
            player->defending = 1;
            WriteConsoleA(con, "You take a defensive stance, expecting the assaults of your adversary,\nbolstering your defense for the next turn.\n", 115, &written, NULL);
            mciSendStringA("play sound\\bolster.wav", NULL, 0, NULL);
            Sleep(3000);
            break;

        case '3':
		    WriteConsoleA(con, "You have decided your chances of winning have faltered,\nand cowardly sprint away from your adversaries...\n", 107, &written, NULL);
            mciSendStringA("play sound\\run.wav", NULL, 0, NULL);
            Sleep(2000);
            if(rand() % 2 == 0){
				Sleep(4000);
			}
			else{
				WriteConsoleA(con, "\n...but even that you do sloppily. The enemy could hit you one last time...\n", 76, &written, NULL);

				mciSendStringA("play sound\\zombieatt.wav", NULL, 0, NULL);
	            sprintf(buffer, "The enemy dealt %d damage to you.\n", enemy_turn(con, player, enemy));
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
                Sleep(5000);
			}
			player->escaped = 1;	
			break;
        
        case '4':
            WriteConsoleA(con, "W.I.P\n", 6, &written, NULL);
            break;
    }

}

void battle(HANDLE con, entity_t *player, inventory_t *inv){
    DWORD written;
    char buffer[CONSOLE_COLS];
    entity_t *enemy = make_enemy();
    player->defending = 0;
    int m_dmg;
    WriteConsoleA(con, "Curses - you're under attack!\n", 31, &written, NULL);
    mciSendStringA("play sound\\battlestart.wav", NULL, 0, NULL);

    while(1){
        player_turn(con, player, enemy);
        if(player->hp <= 0){
            defeat(con);
            //sleep(2000);
            return;
        }

        if(player->escaped == 1){
            //sleep(2000);
            return;
        }

        if(enemy->hp <= 0){
            victory(con, player, enemy, inv);
            return;
        }


        m_dmg = enemy_turn(con, player, enemy);
        mciSendStringA("play sound\\zombieatt.wav", NULL, 0, NULL);
	    sprintf(buffer, "The enemy dealt %d damage to you.\n", m_dmg);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
	    Sleep(1400);

        if(player->hp <= 0){
            defeat(con);
            return;
        }
    }
}
