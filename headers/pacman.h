#ifndef PACMAN_H
# define PACMAN_H

// SECTION: CONSTANTS  
#define FPS 15
#define FRAME_DURATION (1000000 / FPS)
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
#define BERRY_TRACKER_ROWS 35
#define BERRY_TRACKER_COLS 104
#define BORDER_LEFT 20
#define BORDER_RIGHT 100
#define BORDER_TOP 1
#define BORDER_BOTTOM 27
#define TITLE_ROW 2
#define TITLE_COL 27
#define BERRY_START_ROW 4
#define BERRY_END_ROW 24
#define BERRY_START_COL 22
#define BERRY_END_COL 78
#define HORIZONTAL_BORDER_START 22
#define HORIZONTAL_BORDER_END 99
#define BORDER_WIDTH 2
#define HORIZONTAL_OFFSET 25
#define VERTICAL_TOP_OFFSET 4
#define VERTICAL_BOTTOM_OFFSET 18
#define INNER_BORDER_OFFSET 7
#define INNER_BORDER_LENGTH 6

// SECTION: INCLUDES
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "curses.h"

// SECTION: MAIN
void print_menu();
int gameplay(WINDOW *win);
void game_over_screen(WINDOW *win, int score);

// SECTION: GRAPHICS
void draw_borders();
void level1();

// SECTION: UTILS
chtype get_char_at(WINDOW *win, int y, int x);

// SECTION: STRUCTS
// generic vector
typedef struct vector {
    int x;
    int y;
} vec;

typedef struct berrytrack {
    int x, y;
    bool iseaten;
} berrytrack;

// SECTION: GHOSTS LIST
typedef struct ghosts {
    vec *ghost;
    vec *gdir;
    void *next;
} ghosts;
ghosts *add_ghost(ghosts *head, vec *ghost, vec *gdir);
ghosts *remove_ghost(ghosts *head, int x, int y);
void free_ghosts(ghosts *head);

// SECTION: MECHANICS
void spawn_berries(berrytrack berry_tracker[35][104]);
void move_ghost(ghosts *ghost);
void update_orb(vec* orb, int* orb_time, bool* orb_effect);


// SECTION: SCORE SAVING
bool get_initials(const char *prompt, int score);
typedef struct score_block {
    int score;
    char initials[3];
} score_block;
void print_scores();

# endif