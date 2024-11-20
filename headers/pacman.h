#ifndef PACMAN_H
# define PACMAN_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "curses.h"


// SECTION : MAIN
void print_menu();
int gameplay(WINDOW *win);

// SECTION : GRAPHICS
void draw_borders();

void level1();

// SECTION: UTILS
chtype get_char_at(WINDOW *win, int y, int x);


// SECTION : STRUCTS
// generic vector
typedef struct vector {
    int x;
    int y;
} vec;

//berry
typedef struct berrytrack {
    int x, y;
    bool iseaten;
} berrytrack;

//scores
typedef struct scoreblock {
    int score;
    char initials[3];
} scoreblock;

// SECTION: MECHANICS
void spawn_berries(berrytrack berry_tracker[35][104]);
vec *move_ghost(vec *ghostcords, vec *gdir, bool *hit);

# endif