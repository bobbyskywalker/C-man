#include "curses.h"
#include "../headers/pacman.h"

chtype get_char_at(WINDOW *win, int y, int x) {
    wmove(win, y, x);
    return winch(win);
}

void update_orb(vec* orb, int* orb_time, bool* orb_effect) {
    char character = 0;
    if (*orb_effect) {
        do {
            orb->x = rand() % (HORIZONTAL_BORDER_END - HORIZONTAL_BORDER_START + 1) + HORIZONTAL_BORDER_START;
            orb->y = rand() % (BORDER_BOTTOM - BORDER_TOP + 1) + BORDER_TOP;
            chtype bdcheck = get_char_at(stdscr, orb->y, orb->x);
            character = bdcheck & A_CHARTEXT;
        } while (character == '_' || character == '|');
        (*orb_time)--;
    } else {
        attron(COLOR_PAIR(69));
        mvaddch(orb->y, orb->x, '@');
        attroff(COLOR_PAIR(69));
    }
    if (*orb_time == 0) {
        *orb_time = FPS * 10;
        *orb_effect = false;
    }
}