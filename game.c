#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "curses.h"
#include "gamefiles.h"

#define HEIGHT 30
#define WIDTH 120
#define CAPACITY 3000000

typedef struct vector {
    int x;
    int y;
} vec;


chtype get_char_at(WINDOW *win, int y, int x) {
    wmove(win, y, x);
    return winch(win);
}


//TODO: ghosts, power orbs, lifes and menu connection

int gameplay() {
    //initialize screen
    int screenwidth, screenheight;
    WINDOW *win = initscr();
    int score = 0;
    getmaxyx(stdscr, screenheight, screenwidth);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    //pac-man
    vec pacman = {WIDTH / 2, HEIGHT / 2 + 3};
    vec dir = {1, 0};
    int exit = 0;
    berrytrack berrytracker[35][104];

    //game loop
    while (exit != 27) {
        curs_set(0);
        noecho();
        int pressed = wgetch(win);
        vec last_empty = {pacman.x, pacman.y};
        //key reaction
        switch (pressed) {
            case KEY_LEFT:
                dir.x = -1;
                dir.y = 0;
                break;
            case KEY_RIGHT:
                dir.x = 1;
                dir.y = 0;
                break;
            case KEY_UP:
                dir.x = 0;
                dir.y = -1;
                break;
            case KEY_DOWN:
                dir.x = 0;
                dir.y = 1;
                break;
                //escape to quit
            case 27:
                exit = pressed;
                break;
        }
        pacman.x += dir.x;
        pacman.y += dir.y;

        //border collision
        chtype bdcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char character = bdcheck & A_CHARTEXT;
        if (character == '-' || character == '|') {
            pacman.x = last_empty.x;
        }
        if (character == '-' || character == '|') {
            pacman.y = last_empty.y;
        } else if (pacman.y == 3) {
            pacman.y++;
        } else if (pacman.y == 27) {
            pacman.y--;
        }
        //berry consumption mechanism, score update
        if (character == '.') {
            berrytracker[pacman.y - 4][pacman.x - 22].iseaten = true;
            score++;
        }
        erase();
        start_color();
        //add map
        draw_borders();
        spawn_berries(berrytracker);
        //add pac
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvaddch(pacman.y, pacman.x, 'C');
        attroff(COLOR_PAIR(1));
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(2, 96 - 6, "SCORE:");
        mvprintw(2, 97, "%d", score);
        usleep(50000);
    }
    getch();
    return 0;
}
