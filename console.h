#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Windows.h>

/* holds variables related to the console i/o */

typedef struct _console {
    uint32_t px_width; /* width of console window */
    uint32_t px_height; /* height of console window */
    uint32_t cols; /* width of console in characters */
    uint32_t rows; /* height of console in characters */
    HANDLE hcon; /* console handle */
} console_t;


void console_clear();
console_t console_init(uint32_t px_width, uint32_t px_height, uint32_t cols, uint32_t rows);
void console_set_size(uint32_t width, uint32_t height);
void console_write_buffer(console_t *con, uint8_t buffer[], uint32_t width, uint32_t height);

#endif