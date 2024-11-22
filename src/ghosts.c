#include "../headers/pacman.h"

ghosts *add_ghost(ghosts *head, vec *ghost, vec *gdir) {
    ghosts *new = malloc(sizeof(ghosts));
    if (new == NULL) {
        return NULL; // Memory allocation failed
    }
    new->ghost = ghost;
    new->gdir = gdir;
    new->next = head;
    return new;
}

ghosts *remove_ghost(ghosts *head, int x, int y) {
    ghosts *current = head;
    ghosts *prev = NULL;

    while (current != NULL) {
        int ghost_x = current->ghost->x;
        int ghost_y = current->ghost->y;

        // Calculate Manhattan distance
        int dist_x = abs(ghost_x - x);
        int dist_y = abs(ghost_y - y);

        // Check if within a 3-cell radius
        if (dist_x <= 3 && dist_y <= 3) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return head;  // Ghost removed, return updated list
        }

        // Move to the next node
        prev = current;
        current = current->next;
    }

    return head;  // No ghost removed, return original list
}


void check_collision(ghosts *ghost, char character, int next_y, int next_x) {
    if (character == '-' || character == '|') {
        if (character == '-') {  // hit horiz wall
            ghost->gdir->y = 0;
            ghost->gdir->x = (rand() % 2 == 0) ? 1 : -1;  // move left or right randomly
        } else if (character == '|') {  // hit vert wall
            ghost->gdir->x = 0;
            ghost->gdir->y = (rand() % 2 == 0) ? 1 : -1;  // move up or down randomly
        }
        
        if (get_char_at(stdscr, next_y - 1, next_x) == '|') {  // top side
            ghost->gdir->x = (rand() % 2 == 0) ? 1 : -1; // randomly move left or right
            ghost->gdir->y = -1; // Move up
        } else if (get_char_at(stdscr, next_y + 1, next_x) == '|') {  // bottom side
            ghost->gdir->x = (rand() % 2 == 0) ? 1 : -1; // randomly move left or right
            ghost->gdir->y = 1; // Move down
        } else if (get_char_at(stdscr, next_y, next_x + 1) == '-') {  // right side
            ghost->gdir->x = -1; // Move left
            ghost->gdir->y = (rand() % 2 == 0) ? 1 : -1;  // randomly move up or down
        } else if (get_char_at(stdscr, next_y, next_x - 1) == '-') {  // left side
            ghost->gdir->x = 1; // Move right
            ghost->gdir->y = (rand() % 2 == 0) ? 1 : -1;  // randomly move up or down
        }
    } else {
        ghost->ghost->x = next_x;
        ghost->ghost->y = next_y;
    }

    if (ghost->ghost->y <= 4) {  //top border
        ghost->gdir->y = 1;
        ghost->gdir->x = (rand() % 2 == 0) ? 1 : -1;
    } else if (ghost->ghost->y >= 26) {  // bottom border
        ghost->gdir->y = -1;  // Move up
        ghost->gdir->x = (rand() % 2 == 0) ? 1 : -1;
    }
}

void move_ghost(ghosts *ghost) {
    int next_x = ghost->ghost->x + ghost->gdir->x;
    int next_y = ghost->ghost->y + ghost->gdir->y;

    chtype bdcheck = get_char_at(stdscr, next_y, next_x);
    char character = bdcheck & A_CHARTEXT;

    check_collision(ghost, character, next_y, next_x);
}

