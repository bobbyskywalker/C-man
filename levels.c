#include "curses.h"
#include "gamefiles.h"

void level1() {
    char vert = '|';
    char horiz = '_';
    init_pair(30, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(30));
    //upper vertical borders
    for (int i = 60 - 10, k = 60 - 9, j = 4; j < 13; j++) {
        if (j == 6 || j == 7 || j == 8) continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }
    for (int i = 60 + 10, k = 60 + 11, j = 4; j < 13; j++) {
        if (j == 6 || j == 7 || j == 8) continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }
    //lower vertical borders
    for (int i = 60 - 10, k = 60 - 9, j = 27 - 9; j < 28; j++) {
        if (j == 25 || j == 24 || j == 23) continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }
    for (int i = 60 + 10, k = 60 + 11, j = 27 - 9; j < 28; j++) {
        if (j == 25 || j == 24 || j == 23) continue;
        mvaddch(j, i, vert);
        mvaddch(j, k, vert);
    }

    //upper horizontal borders
    for (int i = 25, j = 12, k = 11; i < 60 - 10; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }
    for (int i = 100 - 28, j = 12, k = 11; i < 100 - 3; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }
    //lower horizontal borders
    for (int i = 25, j = 27 - 10, k = j + 1; i < 60 - 10; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }
    for (int i = 100 - 28, j = 27 - 10, k = j + 1; i < 100 - 3; i++) {
        mvaddch(j, i, horiz);
        mvaddch(k, i, horiz);
    }

    //1st quarter border
    for (int i = 6, j = 25 + 7; i < 9; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = 5, j = 25 + 7; j < 25 + 13; j++) {
        mvaddch(i, j, horiz);
    }
    //2nd quarter border
    for (int i = 22, j = 25 + 7; i < 25; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = 25, j = 25 + 7; j < 25 + 13; j++) {
        mvaddch(i, j, horiz);
    }
    //3rd quarter border
    for (int i = 6, j = 120 - 30; i < 9; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = 5, j = 120 - 30; j > 120 - 36; j--) {
        mvaddch(i, j, horiz);
    }
    //4th quarter border
    for (int i = 22, j = 120 - 30; i < 25; i++) {
        mvaddch(i, j, vert);
    }
    for (int i = 25, j = 120 - 30; j > 120 - 36; j--) {
        mvaddch(i, j, horiz);
    }
    attroff(COLOR_PAIR(30));
}
