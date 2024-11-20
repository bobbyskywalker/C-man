#include "curses.h"
#include "../headers/pacman.h"

void level1() {
    char vert = '|';
    char horiz = '-';

    init_pair(42, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(42));

    // upper vertical borders
    for (int i = SCREEN_WIDTH / 2 - BORDER_WIDTH; i <= SCREEN_WIDTH / 2 + BORDER_WIDTH; i++) {
        for (int j = VERTICAL_TOP_OFFSET; j < VERTICAL_TOP_OFFSET + 9; j++) {
            mvaddch(j, i, vert);
        }
    }
    // lower vertical borders
    for (int i = SCREEN_WIDTH / 2 - BORDER_WIDTH; i <= SCREEN_WIDTH / 2 + BORDER_WIDTH; i++) {
        for (int j = VERTICAL_BOTTOM_OFFSET; j < VERTICAL_BOTTOM_OFFSET + 9; j++) {
            mvaddch(j, i, vert);
        }
    }
    // short borders
    for (int i = SCREEN_WIDTH / 2 - 10; i <= SCREEN_WIDTH / 2 + 10; i++) {
        if ((i - (SCREEN_WIDTH / 2 - 10)) % 4 == 0) {  // Check if the index is a multiple of 4
            for (int j = VERTICAL_TOP_OFFSET; j < VERTICAL_TOP_OFFSET + 5; j++) {
                mvaddch(j, i, vert);
            }
        }
    }
    // short borders 2
    for (int i = SCREEN_WIDTH / 2 - 10; i <= SCREEN_WIDTH / 2 + 10; i++) {
        if ((i - (SCREEN_WIDTH / 2 - 10)) % 4 == 0) {  // Check if the index is a multiple of 4
            for (int j = VERTICAL_BOTTOM_OFFSET + 4; j < VERTICAL_BOTTOM_OFFSET + 9; j++) {
                mvaddch(j, i, vert);
            }
        }
    }
    // top horizontal borders
    for (int i = HORIZONTAL_OFFSET - 4; i <= SCREEN_WIDTH / 2 - 10; i++) {
        mvaddch(VERTICAL_TOP_OFFSET + 7, i, horiz);
        mvaddch(VERTICAL_TOP_OFFSET + 8, i, horiz);
    }
    for (int i = SCREEN_WIDTH - HORIZONTAL_OFFSET + 4; i >= SCREEN_WIDTH / 2 + 10; i--) {
        mvaddch(VERTICAL_TOP_OFFSET + 7, i, horiz);
        mvaddch(VERTICAL_TOP_OFFSET + 8, i, horiz);
    }

    // bottom horizontal borders
    for (int i = HORIZONTAL_OFFSET - 4; i <= SCREEN_WIDTH / 2 - 10; i++) {
        mvaddch(VERTICAL_BOTTOM_OFFSET, i, horiz);
        mvaddch(VERTICAL_BOTTOM_OFFSET + 1, i, horiz);
    }
    for (int i = SCREEN_WIDTH - HORIZONTAL_OFFSET + 4; i >= SCREEN_WIDTH / 2 + 10; i--) {
        mvaddch(VERTICAL_BOTTOM_OFFSET, i, horiz);
        mvaddch(VERTICAL_BOTTOM_OFFSET + 1, i, horiz);
    }

    attroff(COLOR_PAIR(42));
}


