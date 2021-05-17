#include "graphics.h"

char *concat(char *str1, char *str2) {
    char *output = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}

void console_cursor_hide(HANDLE con) {
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(con, &info);
}

void console_clear(HANDLE con) {
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(con, &screen);
    FillConsoleOutputCharacterA(con, ' ', screen.dwSize.X * screen.dwSize.Y, (COORD){0, 0}, &written);
    SetConsoleCursorPosition(con, (COORD){0, 0});
}

void console_set_size(int width, int height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

int display_dialogue_box(HANDLE con, char *text, char **opts, int nopts) {
    int len = 0, cur_len = 0, max_len = 0;
    int selected = 0;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    char *buffer = (char*)malloc(CONSOLE_COLS * nopts);
    SetConsoleCursorPosition(con, (COORD){0, 1});
    WriteConsoleA(con, text, strlen(text), &written, NULL);
    GetConsoleScreenBufferInfo(con, &screen);
    max_len = strlen(text);
    for (int i = 0; i < nopts; ++i) {
        len += sprintf(buffer + len, " %s\n", opts[i]);
        cur_len = snprintf(NULL, 0, " %s\n", opts[i]);
        if (cur_len > max_len) max_len = cur_len;
    }
    for (int i = 1; i < nopts + screen.dwCursorPosition.Y; ++i) {
        FillConsoleOutputCharacterA(con, ' ', max_len, (COORD){0, i}, &written);
    }
    SetConsoleCursorPosition(con, (COORD){0, 1});
    WriteConsoleA(con, text, strlen(text), &written, NULL);
    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    

    FillConsoleOutputCharacterA(con, '-', max_len, (COORD){0, nopts + screen.dwCursorPosition.Y}, &written);
    for (int i = 1; i <= nopts + screen.dwCursorPosition.Y; ++i) FillConsoleOutputCharacterA(con, '|', 1, (COORD){max_len, i}, &written);
    FillConsoleOutputCharacterA(con, '+', 1, (COORD){max_len, nopts + screen.dwCursorPosition.Y}, &written);

    FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, screen.dwCursorPosition.Y}, &written);
    while (1) {
        getch();
        FillConsoleOutputCharacterA(con, ' ', 1, (COORD){0, selected + screen.dwCursorPosition.Y}, &written);

        if ((GetAsyncKeyState(0x57) & 0x8000) != 0) selected--;
        else if ((GetAsyncKeyState(0x53) & 0x8000) != 0) selected++;
        else if ((GetAsyncKeyState(0x45) & 0x8000) != 0) break;

        if (selected < 0) selected = 0;
        if (selected > nopts - 1) selected = nopts - 1;
        FillConsoleOutputCharacterA(con, '>', 1, (COORD){0, selected + screen.dwCursorPosition.Y}, &written);
    }

    free(buffer);
    return selected;
}

void draw(HANDLE con, world_t *w) {
    DWORD written;
    char status[COLS + 1];
    char *frame;
    //if (cheat == 2) sprintf(status, "HP: %d/%d | DMG: %d | COINS: %d | LVL: %d | ENEMIES: %d | POS: %d %d | EXIT: %d %d ",
    //    w->player->hp, player_max_hp, w->player->dmg, w->player->coins, w->depth, w->enemy_count, w->player->x, w->player->y, w->exit_x, w->exit_y);
    sprintf(status, "HP: %d/%d | DMG: %d | COINS: %d | LVL: %d | ENEMIES: %d ", w->player->hp, player_max_hp, w->player->dmg, w->player->coins, w->depth, w->enemy_count);
    for (int i = strlen(status); i < COLS + 1; ++i) {
        status[i] = '=';
    }
    status[COLS] = '\0';
    if (cheat == 0) {
        apply_fov(w, fov_map, 5, 3);
        frame = concat(status, fov_map);
    }
    else frame = concat(status, w->map);
    WriteConsoleOutputCharacterA(con, frame, CONSOLE_ROWS * CONSOLE_COLS, (COORD){0, 0}, &written);
}

void draw_town(HANDLE con, world_t *w) {
    DWORD written;
    //WriteConsoleOutputCharacterA(con, frame, CONSOLE_ROWS * CONSOLE_COLS, (COORD){0, 0}, &written);
    //SetConsoleCursorPosition(con, (COORD){0, 0});
    //char buf[COLS];
    //sprintf(buf, "X: %d Y: %d     ", w->player->x, w->player->y);
    //WriteConsoleA(con, buf, strlen(buf), &written, NULL);
    WriteConsoleOutputCharacterA(con, town_art, CONSOLE_ROWS * CONSOLE_COLS, (COORD){0, 0}, &written);
    FillConsoleOutputCharacterA(con, PLAYER, 1, (COORD){w->player->x, w->player->y}, &written);
}



void draw_border(HANDLE con) {
    DWORD written;
    //SetConsoleCursorPosition(con, (COORD){1, 1});
    //WriteConsoleA(con, "+", 1, &written, NULL);
    FillConsoleOutputCharacterA(con, 201, 1, (COORD){0, 0}, &written);
    
    //SetConsoleCursorPosition(con, (COORD){CONSOLE_COLS - 1, 1});
    //WriteConsoleA(con, "+", 1, &written, NULL);
    FillConsoleOutputCharacterA(con, 187, 1, (COORD){CONSOLE_COLS - 1, 0}, &written);

    //SetConsoleCursorPosition(con, (COORD){1, CONSOLE_ROWS - 1});
    //WriteConsoleA(con, "+", 1, &written, NULL);
    FillConsoleOutputCharacterA(con, 200, 1, (COORD){0, CONSOLE_ROWS - 1}, &written);
    
    //SetConsoleCursorPosition(con, (COORD){CONSOLE_COLS - 1, CONSOLE_ROWS - 1});
    //WriteConsoleA(con, "+", 1, &written, NULL);

    FillConsoleOutputCharacterA(con, 188, 1, (COORD){CONSOLE_COLS - 1, CONSOLE_ROWS - 1}, &written);
    
    FillConsoleOutputCharacterA(con, 205, CONSOLE_COLS - 2, (COORD){1, 0}, &written);
    FillConsoleOutputCharacterA(con, 205, CONSOLE_COLS - 2, (COORD){1, CONSOLE_ROWS - 1}, &written);

    for (int i = 1; i <= CONSOLE_ROWS - 2; ++i) {
        FillConsoleOutputCharacterA(con, 186, 1, (COORD){0, i}, &written);
        FillConsoleOutputCharacterA(con, 186, 1, (COORD){CONSOLE_COLS - 1, i}, &written);
    }

    SetConsoleCursorPosition(con, (COORD){1, CONSOLE_ROWS - 2});
    WriteConsoleA(con, "[A]ttack          [D]efend          [E]scape", 45, &written, NULL);

    FillConsoleOutputCharacterA(con, 205, 45, (COORD){1, CONSOLE_ROWS - 3}, &written);

    FillConsoleOutputCharacterA(con, 204, 1, (COORD){0, CONSOLE_ROWS - 3}, &written);
    FillConsoleOutputCharacterA(con, 202, 1, (COORD){46, CONSOLE_ROWS - 1}, &written);
    FillConsoleOutputCharacterA(con, 187, 1, (COORD){46, CONSOLE_ROWS - 3}, &written);
    FillConsoleOutputCharacterA(con, 186, 1, (COORD){46, CONSOLE_ROWS - 2}, &written);
}