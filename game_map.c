#include "curses.h"
#include "gamefiles.h"

#define VERTICAL 30
#define HORIZONTAL 100

//borders 30 / 100

void draw_borders(){
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    char title[] = "C-MAN v.1";
    mvprintw(2, 27, title);
    attroff(COLOR_PAIR(4));
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(3));
    mvaddch(27, 20, '*');
    mvaddch(27, 100, '*');
    mvaddch(1, 20, '*');
    mvaddch(1, 100, '*');
    attroff(COLOR_PAIR(3));
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    //sides
    for(int i = 2; i < 4; i++){
        mvaddch(i, 20, '|');
        mvaddch(i, 100, '|');
    }
    for (int i = 4; i < 27; i++) {
        mvaddstr(i, 20, "|");
        mvaddstr(i, 100, "|");
    }
    //floors
    for (int i = 22; i < 99; i++) {
        mvaddch(1, i, '-');
        mvaddch(3, i, '_');
        mvaddch(27, i, '_');
    }
        level1();
}

