#include "curses.h"
#include "../headers/pacman.h"

// Define macros for constants
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
#define BORDER_WIDTH 2
#define HORIZONTAL_OFFSET 25
#define VERTICAL_TOP_OFFSET 4
#define VERTICAL_BOTTOM_OFFSET 18
#define INNER_BORDER_OFFSET 7
#define INNER_BORDER_LENGTH 6
#define QUARTER_BOX_HEIGHT 3

void level1() {
    char vert = '|';
    char horiz = '_';

    init_pair(30, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(30));

    // Upper vertical borders
    for (int i = SCREEN_WIDTH / 2 - BORDER_WIDTH, 
             k = SCREEN_WIDTH / 2 - BORDER_WIDTH + 1, 
             j = VERTICAL_TOP_OFFSET; j < VERTICAL_TOP_OFFSET + 9; j++) {
        if (j == VERTICAL_TOP_OFFSET + 2 || j == VERTICAL_TOP_OFFSET + 3 || j == VERTICAL_TOP_OFFSET + 4) 
            continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }
    for (int i = SCREEN_WIDTH / 2 + BORDER_WIDTH, 
             k = SCREEN_WIDTH / 2 + BORDER_WIDTH + 1, 
             j = VERTICAL_TOP_OFFSET; j < VERTICAL_TOP_OFFSET + 9; j++) {
        if (j == VERTICAL_TOP_OFFSET + 2 || j == VERTICAL_TOP_OFFSET + 3 || j == VERTICAL_TOP_OFFSET + 4) 
            continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }

    // Lower vertical borders
    for (int i = SCREEN_WIDTH / 2 - BORDER_WIDTH, 
             k = SCREEN_WIDTH / 2 - BORDER_WIDTH + 1, 
             j = VERTICAL_BOTTOM_OFFSET; j < VERTICAL_BOTTOM_OFFSET + BORDER_WIDTH; j++) {
        if (j == VERTICAL_BOTTOM_OFFSET - 2 || j == VERTICAL_BOTTOM_OFFSET - 3 || j == VERTICAL_BOTTOM_OFFSET - 4) 
            continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }
    for (int i = SCREEN_WIDTH / 2 + BORDER_WIDTH, 
             k = SCREEN_WIDTH / 2 + BORDER_WIDTH + 1, 
             j = VERTICAL_BOTTOM_OFFSET; j < VERTICAL_BOTTOM_OFFSET + BORDER_WIDTH; j++) {
        if (j == VERTICAL_BOTTOM_OFFSET - 2 || j == VERTICAL_BOTTOM_OFFSET - 3 || j == VERTICAL_BOTTOM_OFFSET - 4) 
            continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }

    // Upper horizontal borders
    for (int i = HORIZONTAL_OFFSET, j = VERTICAL_TOP_OFFSET + 8, k = VERTICAL_TOP_OFFSET + 7; 
         i < SCREEN_WIDTH / 2 - BORDER_WIDTH; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }
    for (int i = SCREEN_WIDTH - HORIZONTAL_OFFSET - BORDER_WIDTH * 2, j = VERTICAL_TOP_OFFSET + 8, k = VERTICAL_TOP_OFFSET + 7; 
         i < SCREEN_WIDTH - HORIZONTAL_OFFSET; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }

    // Lower horizontal borders
    for (int i = HORIZONTAL_OFFSET, j = VERTICAL_BOTTOM_OFFSET, k = j + 1; 
         i < SCREEN_WIDTH / 2 - BORDER_WIDTH; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }
    for (int i = SCREEN_WIDTH - HORIZONTAL_OFFSET - BORDER_WIDTH * 2, j = VERTICAL_BOTTOM_OFFSET, k = j + 1; 
         i < SCREEN_WIDTH - HORIZONTAL_OFFSET; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }

    // 1st quarter border
    for (int i = VERTICAL_TOP_OFFSET + 2, j = HORIZONTAL_OFFSET + INNER_BORDER_OFFSET; 
         i < VERTICAL_TOP_OFFSET + QUARTER_BOX_HEIGHT; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = VERTICAL_TOP_OFFSET + 1, j = HORIZONTAL_OFFSET + INNER_BORDER_OFFSET; 
         j < HORIZONTAL_OFFSET + INNER_BORDER_OFFSET + INNER_BORDER_LENGTH; j++) {
        mvaddch(i, j, horiz);
    }

    // 2nd quarter border
    for (int i = VERTICAL_BOTTOM_OFFSET - QUARTER_BOX_HEIGHT, j = HORIZONTAL_OFFSET + INNER_BORDER_OFFSET; 
         i < VERTICAL_BOTTOM_OFFSET; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = VERTICAL_BOTTOM_OFFSET, j = HORIZONTAL_OFFSET + INNER_BORDER_OFFSET; 
         j < HORIZONTAL_OFFSET + INNER_BORDER_OFFSET + INNER_BORDER_LENGTH; j++) {
        mvaddch(i, j, horiz);
    }

    // 3rd quarter border
    for (int i = VERTICAL_TOP_OFFSET + 2, j = SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET; 
         i < VERTICAL_TOP_OFFSET + QUARTER_BOX_HEIGHT; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = VERTICAL_TOP_OFFSET + 1, j = SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET; 
         j > SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET - INNER_BORDER_LENGTH; j--) {
        mvaddch(i, j, horiz);
    }

    // 4th quarter border
    for (int i = VERTICAL_BOTTOM_OFFSET - QUARTER_BOX_HEIGHT, j = SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET; 
         i < VERTICAL_BOTTOM_OFFSET; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = VERTICAL_BOTTOM_OFFSET, j = SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET; 
         j > SCREEN_WIDTH - HORIZONTAL_OFFSET - INNER_BORDER_OFFSET - INNER_BORDER_LENGTH; j--) {
        mvaddch(i, j, horiz);
    }

    attroff(COLOR_PAIR(30));
}
