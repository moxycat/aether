#include "battle.h"

entity_t *make_enemy() {
    entity_t *e = (entity_t*)malloc(sizeof(entity_t));
    e->dmg = 3 + rand_int(0, 3);
    e->hp = 50 + rand_int(0, 50);
    e->coins = rand_int(5, 10);
    return e;
}

void attack(entity_t *attacker, entity_t *attackee) {
    attackee->hp -= attacker->dmg;
}

void battle(HANDLE con, entity_t *player) {
    DWORD written;
    int first = rand() % 2;
    int opt = 0;
    int defending = 0;
    int escape = 0;

    entity_t *enemy = make_enemy();
    int p_hp = player->hp;
    int e_hp = enemy->hp;



    SetConsoleCursorPosition(con, (COORD){0, 0});
    
    char buffer[CONSOLE_COLS];
    
    //if (first) WriteConsoleA(con, "You are first to act.\n\n", 24, &written, NULL);
    //else WriteConsoleA(con, "The enemy is first to act.\n\n", 29, &written, NULL);

    while (1) {
        sprintf(buffer, "You  > HP: %d  DMG: %d\nEnemy> HP: %d  DMG: %d\n", player->hp, player->dmg, enemy->hp, enemy->dmg);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
        WriteConsoleA(con, "It is your turn, what will you do?\n\n", 36, &written, NULL);
        WriteConsoleA(con, "1. Attack\n2. Defend\n3. Escape\n4. Info\n\n", 39, &written, NULL);
        do {
            opt = getch();
            if (opt < '1' || opt > '4') WriteConsoleA(con, "That is not a valid action.\n\n", 29, &written, NULL);
        } while (opt < '1' || opt > '4');

        switch (opt) {
            case '1':
                attack(player, enemy);
                sprintf(buffer, "You attack the enemy for %d damage.\n", e_hp - enemy->hp);
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
                break;
            case '2':
                defending = !defending;
                WriteConsoleA(con, "You decide to defend.\n", 22, &written, NULL);
                break;
            case '3':
                escape = !escape;
                WriteConsoleA(con, "You run away.\n", 14, &written, NULL);
                break;
            case '4':
                sprintf(buffer, "Some quirky description specific to the enemy you are currently engaged in combat with.\n");
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
                break;
            default: break;
        }

        if (enemy->hp <= 0) {
            WriteConsoleA(con, "You have defeated the enemy!\n", 29, &written, NULL);
            return;
        }

        attack(enemy, player);
        sprintf(buffer, "The enemy hits you for %d damage.\n", p_hp - player->hp);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);

        if (player->hp <= 0) {
            WriteConsoleA(con, "You died!\n", 10, &written, NULL);
            return;
        }

        p_hp = player->hp;
        e_hp = enemy->hp;

        //WriteConsoleA(con, "Press any key to proceed to the next turn.\n", 43, &written, NULL);
        getch();

        FillConsoleOutputCharacterA(con, ' ', CONSOLE_COLS * CONSOLE_ROWS, (COORD){0, 0}, &written);
        SetConsoleCursorPosition(con, (COORD){0, 0});
    }

}