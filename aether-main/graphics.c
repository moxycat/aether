#include "graphics.h"


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