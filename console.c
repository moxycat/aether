#include "console.h"

void console_clear() {
    COORD topleft  = { 0, 0 };
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(hcon, &screen);
    WriteConsoleOutputCharacterA(hcon, " ", screen.dwSize.X * screen.dwSize.Y, topleft, &written);
    //FillConsoleOutputAttribute(hcon, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
    //    screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    //SetConsoleCursorPosition(hcon, topleft);
}

console_t console_init(uint32_t px_width, uint32_t px_height, uint32_t cols, uint32_t rows) {
    console_t con;
    con.px_width = px_width;
    con.px_height = px_height;
    con.cols = cols;
    con.rows = rows;
    con.hcon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(con.hcon);
    return con;
}

void console_set_size(uint32_t width, uint32_t height) {
    HWND window = GetConsoleWindow();
    RECT rect;
    GetWindowRect(window, &rect);
    MoveWindow(window, rect.left, rect.top, width, height, TRUE);
}

void console_write_buffer(console_t *con, uint8_t buffer[], uint32_t width, uint32_t height) {
    COORD topleft  = { 0, 0 };
    COORD size = { width, height };
    DWORD written;

    WriteConsoleOutputCharacterA(con->hcon, buffer, width * height, topleft, &written);
}

void slowprint(char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        putchar(str[i]);
        Sleep(25);
    }
}