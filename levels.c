#include "curses.h"
#include "gamefiles.h"

#define VERTICAL 30
#define HORIZONTAL 100

void level1() {
    //in-game borders
    char horizshort[] = "-----"; //len 5
    char horizlong[] = "--------------------"; //len 20
    char vert = '|';
    //wallsticked vertical
    for (int i = 27, j = 4; i > 22; i--, j++) {
        mvaddch(i, HORIZONTAL / 2, vert);
        mvaddch(i, HORIZONTAL - 30, vert);
        mvaddch(i, HORIZONTAL - 10, vert);
        mvaddch(i, HORIZONTAL / 4, vert);
        mvaddch(i, HORIZONTAL / 4 + 15, vert);
        mvaddch(j, HORIZONTAL - 10, vert);
        mvaddch(j, HORIZONTAL - 20, vert);
        mvaddch(j, HORIZONTAL - 50, vert);
        mvaddch(j, HORIZONTAL - 35, vert);

    }
    //wallsticked horizontal
    mvaddstr(5, 21, horizshort);
    mvaddstr(9, 21, horizlong);
    mvaddstr(18, 21, horizlong);
    mvaddstr(14, 100 - 20, horizlong);
    //additional
    mvaddch(4, HORIZONTAL - 70, vert);
    mvaddch(5, HORIZONTAL - 70, vert);
    mvaddch(4, HORIZONTAL - 61, vert);
    mvaddch(5, HORIZONTAL - 61, vert);
    mvaddch(6, HORIZONTAL - 61, vert);
    mvaddstr(24, HORIZONTAL / 2 + 1, horizshort);
    mvaddstr(25, HORIZONTAL - 30 - 5, horizshort);
    mvaddstr(25, HORIZONTAL - 30 - 10, horizshort);
    mvaddch(10, HORIZONTAL - 65, vert);
    mvaddch(11, HORIZONTAL - 65, vert);
    mvaddch(12, HORIZONTAL - 65, vert);
    mvaddch(13, HORIZONTAL - 65, vert);
    for (int i = 9; i < 16; i++) {
        mvaddch(i, HORIZONTAL - 35, vert);
    }
    mvaddstr(VERTICAL / 2 - 4, HORIZONTAL - 34, horizlong);
    mvaddstr(VERTICAL / 2 + 5, HORIZONTAL - 20, horizlong);
    for (int i = VERTICAL / 2 + 6; i < 25; i++) {
        mvaddch(i, HORIZONTAL - 17, vert);
    }
    mvaddstr(15, HORIZONTAL - 55, horizlong);
    mvaddch(16, HORIZONTAL - 55, vert);
    mvaddch(17, HORIZONTAL - 55, vert);
    mvaddch(18, HORIZONTAL - 55, vert);
    mvaddch(19, HORIZONTAL - 55, vert);
    mvaddstr(24, HORIZONTAL / 4 + 10, horizshort);
    attroff(COLOR_PAIR(2));
}
