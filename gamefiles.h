#ifndef PACMANGAME_GAMEFILES_H
#define PACMANGAME_GAMEFILES_H

#endif //PACMANGAME_GAMEFILES_H

#include <stdint.h>
#include "curses.h"

void printmenu();

int gameplay(WINDOW *win);

void draw_borders();

void level1();

chtype get_char_at(WINDOW *win, int y, int x);

typedef struct vector {
    int x;
    int y;
} vec;


//berry
typedef struct berrytrack {
    int x, y;
    bool iseaten;
} berrytrack;

void spawn_berries(berrytrack berry_tracker[35][104]);

//ghost
vec *move_ghost(vec *ghostcords, vec *gdir, bool *hit);


//scores
typedef struct scoreblock {
    int score;
    char initials[3];
} scoreblock;


void save_score(int score, WINDOW *win);

void print_score();

FILE *read_score(char *path, WINDOW *win);

scoreblock *sort_score(FILE *score_fileptr);
