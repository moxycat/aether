#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


#include <stdio.h>
#include <Windows.h>

#include "mapgen.h"
#include "const.h"
#include "global.h"

void draw_border(HANDLE con);
void console_cursor_hide(HANDLE con);
void console_clear(HANDLE con);
void console_set_size(int width, int height);
int display_dialogue_box(HANDLE con, char *text, char **opts, int nopts);
void draw(HANDLE con, world_t *w);

#endif