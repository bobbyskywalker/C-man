#include "curses.h"
#include "../headers/pacman.h"

chtype get_char_at(WINDOW *win, int y, int x) {
    wmove(win, y, x);
    return winch(win);
}