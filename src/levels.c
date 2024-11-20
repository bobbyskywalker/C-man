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
    char horiz = '-';

    init_pair(30, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(30));

    // Upper vertical borders
    for (int i = SCREEN_WIDTH / 2 - BORDER_WIDTH; i <= SCREEN_WIDTH / 2 + BORDER_WIDTH; i++) {
        for (int j = VERTICAL_TOP_OFFSET; j < VERTICAL_TOP_OFFSET + 9; j++) {
            if (j == VERTICAL_TOP_OFFSET + 2 || j == VERTICAL_TOP_OFFSET + 3 || j == VERTICAL_TOP_OFFSET + 4)
                continue; // Skip gaps
            mvaddch(j, i, vert);
        }
    }
}

