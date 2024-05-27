#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "curses.h"
#include "gamefiles.h"

vec *move_ghost(vec *ghostcords, vec *gdir, bool *hit) {
    int next_x = ghostcords->x + gdir->x;
    int next_y = ghostcords->y + gdir->y;
    chtype bdcheck = get_char_at(stdscr, next_y, next_x);
    char character = bdcheck & A_CHARTEXT;
    // If the ghost hits a wall ('-' or '|'), change direction
    if (character == '_' || character == '|') {
        if (gdir->x != 0) {  // Moving horizontally
            gdir->x = 0;
            gdir->y = (rand() % 2 == 0) ? 1 : -1;  // Choose a random vertical direction
        } else if (gdir->y != 0) {  // Moving vertically
            gdir->y = 0;
            gdir->x = (rand() % 2 == 0) ? 1 : -1;  // Choose a random horizontal direction
        }
    }else if (character == 'C'){
        hit = (bool *) true;
    }else {
        // Update the ghost's position if there's no wall
        ghostcords->x = next_x;
        ghostcords->y = next_y;
    }
    if(ghostcords->y == 4){
        gdir->y++;
        gdir->x = (rand() % 2 == 0) ? 1 : -1;
    }else if(ghostcords->y == 26){
        gdir->y--;
        gdir->x = (rand() % 2 == 0) ? 1 : -1;
    }
    return ghostcords;
}

