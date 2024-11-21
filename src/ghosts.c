#include <stdlib.h>
#include <stdbool.h>
#include "curses.h"
#include "../headers/pacman.h"


// hit param
vec *move_ghost(vec *ghostcords, vec *gdir) {
    int next_x = ghostcords->x + gdir->x;
    int next_y = ghostcords->y + gdir->y;
    chtype bdcheck = get_char_at(stdscr, next_y, next_x);
    char character = bdcheck & A_CHARTEXT;
    // If the ghost hits a wall ('-' or '|'), change direction
   if (character == '-' || character == '|') {
    if (character == '-') {  // Hit horizontal wall
        gdir->y = 0;
        gdir->x = (rand() % 2 == 0) ? 1 : -1;  // Move left or right
    } else if (character == '|') {  // Hit vertical wall
        gdir->x = 0;
        gdir->y = (rand() % 2 == 0) ? 1 : -1;  // Move up or down
    } else if (get_char_at(stdscr, next_y, next_x) == '-' && get_char_at(stdscr, next_y, next_x+1) == '|') {
        gdir->x = (rand() % 2 == 0) ? -1 : 0;
        gdir->y = (rand() % 2 == 0) ? -1 : 0;
    } else if (get_char_at(stdscr, next_y, next_x) == '|' && get_char_at(stdscr, next_y, next_x-1) == '-') {
        // Hit top-right corner, move either right or up
        gdir->x = (rand() % 2 == 0) ? 1 : 0;
        gdir->y = (rand() % 2 == 0) ? -1 : 0;
    } else if (get_char_at(stdscr, next_y, next_x) == '|' && get_char_at(stdscr, next_y+1, next_x) == '-') {
        gdir->x = (rand() % 2 == 0) ? -1 : 0;
        gdir->y = (rand() % 2 == 0) ? 1 : 0;
    } else if (get_char_at(stdscr, next_y, next_x) == '-' && get_char_at(stdscr, next_y+1, next_x) == '|') {
        gdir->x = (rand() % 2 == 0) ? 1 : 0;
        gdir->y = (rand() % 2 == 0) ? 1 : 0;
    }
    // } else if (character == 'C') {
    //     hit = (bool *) true;
    } else {
        // Update the ghost's position if there's no wall
        ghostcords->x = next_x;
        ghostcords->y = next_y;
    }
    if (ghostcords->y == 4) {
        gdir->y++;
        gdir->x = (rand() % 2 == 0) ? 1 : -1;
    } else if (ghostcords->y == 26) {
        gdir->y--;
        gdir->x = (rand() % 2 == 0) ? 1 : -1;
    }
    return ghostcords;
}

