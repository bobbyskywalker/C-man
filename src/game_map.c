#include "curses.h"
#include "../headers/pacman.h"

// Spawning berries, generic, adjustable loop
void spawn_berries(berrytrack berry_tracker[BERRY_TRACKER_ROWS][BERRY_TRACKER_COLS]) {
    vec berry = {0, 0};
    chtype is_berryspot;

    
    for (int i = 0; i < BERRY_END_ROW; i++) {
        for (int j = 0; j < BERRY_END_COL; j++) {
            berry.x = BERRY_START_ROW + i;
            berry.y = BERRY_START_COL + j;

            if (berry_tracker[i][j].iseaten) {
                continue;
            }

            is_berryspot = mvinch(berry.x, berry.y);
            char isblank = is_berryspot & A_CHARTEXT;

            if (isblank == ' ' || isblank == '.') {
                mvaddch(berry.x, berry.y, '.'); // Draw the berry
            }
        }
    }
}

void draw_borders() {
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    mvprintw(TITLE_ROW, TITLE_COL, "C-MAN v.1");
    attroff(COLOR_PAIR(4));

    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(3));
    mvaddch(BORDER_BOTTOM, BORDER_LEFT, '*');
    mvaddch(BORDER_BOTTOM, BORDER_RIGHT, '*');
    mvaddch(BORDER_TOP, BORDER_LEFT, '*');
    mvaddch(BORDER_TOP, BORDER_RIGHT, '*');
    attroff(COLOR_PAIR(3));

    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    for (int i = BORDER_TOP + 1; i < BORDER_BOTTOM; i++) {
        mvaddch(i, BORDER_LEFT, '|');
        mvaddch(i, BORDER_RIGHT, '|');
    }

    for (int i = HORIZONTAL_BORDER_START; i < HORIZONTAL_BORDER_END; i++) {
        mvaddch(BORDER_TOP, i, '-');
        mvaddch(BORDER_TOP + 2, i, '_');
        mvaddch(BORDER_BOTTOM, i, '_');
    }

    attroff(COLOR_PAIR(2));

    level1();
}
