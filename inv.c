#include "inv.h"

int inventory_calc_size(inventory_t *inv) {
    int size = 0;
    for (int i = 0; i < ITEM_COUNT; ++i) {
        size += inv->items[i].quantity;
    }
    return size;
}

void inventory_draw(HANDLE con, inventory_t *inv) {
    DWORD written;
    char buffer[CONSOLE_COLS * ITEM_COUNT];
    int key;
    int selected = 0;
    int items = 0;
    int skipped = 0;
    int true_selected = 0;
    int len = 0;
    int current_len = 0;
    int max_len = 0;
    SetConsoleCursorPosition(con, (COORD){0, 1}); /* don't mess up the status bar at the top */

    max_len = sprintf(buffer, "Equipped: %s\n", (inv->equipped == -1) ? "nothing" : inv->items[inv->equipped].name);

    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);

    
    for (int i = 0; i < ITEM_COUNT; ++i) {
        if (inv->items[i].quantity >= 0) {
            len += sprintf(buffer + len, " %s - %d\n", inv->items[i].name, inv->items[i].quantity);
            current_len = snprintf(NULL, 0, " %s - %d\n", inv->items[i].name, inv->items[i].quantity);
            if (current_len > max_len) max_len = current_len;
            items++;
        }
        else skipped++;
    }
    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);

    FillConsoleOutputCharacterA(con, '-', max_len, (COORD){0, items + 2}, &written);
    for (int i = 1; i <= items + 2; ++i) FillConsoleOutputCharacterA(con, '|', 1, (COORD){max_len, i}, &written);
    FillConsoleOutputCharacterA(con, '+', 1, (COORD){max_len, items + 2}, &written);
    
    FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, selected + 2}, &written);
    while (1) {
        key = getch();
        FillConsoleOutputCharacterA(con, ' ', 1, (COORD){0, selected + 2}, &written);

        if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
            selected--;
        }
        else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
            selected++;
        }
        else if ((GetAsyncKeyState(VK_TAB) & 0x8000) != 0) {
            return;
        }
        else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) {
            inv->equipped = selected;
        }
        if (selected < 0) selected = 0;
        if (selected > items - 1) selected = items - 1;
        FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, selected + 2}, &written);
        
        SetConsoleCursorPosition(con, (COORD){0, 1});
        len = sprintf(buffer, "Equipped: %s\n", (inv->equipped == -1) ? "nothing" : inv->items[inv->equipped].name);
        FillConsoleOutputCharacterA(con, ' ', max_len, (COORD){0, 1}, &written);
        for (int i = 1; i <= items + 2; ++i) FillConsoleOutputCharacterA(con, ' ', 1, (COORD){max_len, i}, &written);
        if (len > max_len) max_len = len;
        
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);

        FillConsoleOutputCharacterA(con, '-', max_len, (COORD){0, items + 2}, &written);
        
        for (int i = 1; i <= items + 2; ++i) FillConsoleOutputCharacterA(con, '|', 1, (COORD){max_len, i}, &written);
        FillConsoleOutputCharacterA(con, '+', 1, (COORD){max_len, items + 2}, &written);
    }
}

void inventory_init(inventory_t *inv, int quantities[]) {
    for (int i = 0; i < ITEM_COUNT; ++i) {
        inv->items[i].quantity = quantities[i];
        inv->items[i].name = item_names[i];
        inv->items[i].dmg = 0;
    }
    inv->equipped = -1;
}

void drops(HANDLE con, inventory_t *inv){
    DWORD written;
    char buffer[CONSOLE_COLS];

    int drop = rand() % 6;
    int quan;

    if(drop < 4){
        inv->items[drop].quantity++;
        sprintf(buffer, "The monster dropped a %s!\n", inv->items[drop].name);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    }

    else if(drop == 4){
        quan = rand_int(2, 4);
        inv->items[6].quantity += quan;
        sprintf(buffer, "The monster dropped a %d pieces of ore!\n", quan);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    }
}