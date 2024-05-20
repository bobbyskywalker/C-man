#ifndef PACMANGAME_GAMEFILES_H
#define PACMANGAME_GAMEFILES_H

#endif //PACMANGAME_GAMEFILES_H
#include <stdint.h>
#include "curses.h"

void printmenu();

int gameplay();

void draw_borders();

void level1();

chtype get_char_at(WINDOW *win, int y, int x);

typedef struct berrytrack{
    int x,y;
    bool iseaten;
}berrytrack;

void spawn_berries(berrytrack berry_tracker[35][104]);