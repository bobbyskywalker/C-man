#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "curses.h"
#include "gamefiles.h"

#define HEIGHT 30
#define WIDTH 120

chtype get_char_at(WINDOW *win, int y, int x) {
    wmove(win, y, x);
    return winch(win);
}

//TODO: power orbs and menu connection

int gameplay() {
    //initialize screen
    int screenwidth, screenheight;
    WINDOW *win = initscr();
    int score = 0;
    int lives = 3;
    char lifestr[] = "<3:";
    getmaxyx(stdscr, screenheight, screenwidth);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    //pac-man variables
    vec pacman = {WIDTH / 2, HEIGHT / 2 + 3};
    vec dir = {1, 0};

    //ghost variables
    vec *ghost1 = malloc(2 * sizeof(int));
    vec *ghost2 = malloc(2 * sizeof(int));
    vec *ghost3 = malloc(2 * sizeof(int));
    ghost1->x = 25; ghost1->y = 6;
    ghost2->x = 90; ghost2->y = 8;
    ghost3->x = 30; ghost3->y = 22;
    vec *gdir1 = malloc(2 * sizeof(int));
    gdir1->x = 1; gdir1->y = 0;
    vec *gdir2 = malloc(2 * sizeof(int));
    gdir2->x = 1; gdir2->y = 0;
    vec *gdir3 = malloc(2 * sizeof(int));
    gdir3->x = 0; gdir3->y = 1;

    //berry array
    berrytrack berrytracker[35][104];

    int exit = 0;
    bool *hit = false;
    //game loop
    while (exit != 27) {
        curs_set(0);
        noecho();
        int pressed = wgetch(win);
        vec last_empty_pac = {pacman.x, pacman.y};

        //ghost collision, -1 life
        chtype killcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char killchar = killcheck & A_CHARTEXT;
        if (killchar == '#') hit = (bool *) true;
        if (hit == true) {
            lives--;
            hit = false;
        }
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


        //border collision: pacman
        chtype bdcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char character = bdcheck & A_CHARTEXT;

        if (character == '-' || character == '|') {
            pacman.x = last_empty_pac.x;
        }
        if (character == '-' || character == '|') {
            pacman.y = last_empty_pac.y;
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

        //ghosts
        ghost1 = move_ghost(ghost1, gdir1, hit);
        ghost2 = move_ghost(ghost2, gdir2, hit);
        ghost3 = move_ghost(ghost3, gdir3, hit);

        if (lives == 0) {
            break;
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
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        attron(COLOR_PAIR(5));
        mvaddch(ghost1->y, ghost1->x, '#');
        mvaddstr(ghost2->y, ghost2->x, "#");
        mvaddch(ghost3->y, ghost3->x, '#');
        attroff(COLOR_PAIR(5));
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(2, 95 - 6, "SCORE:");
        mvprintw(2, 95, "%d", score);
        init_pair(6, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(6));
        mvprintw(2, WIDTH / 2 - sizeof(lifestr) + 5, lifestr);
        mvprintw(2, WIDTH / 2 - sizeof(lifestr) + 8, "%d", lives);
        attroff(COLOR_PAIR(6));
        usleep(65000);
    }
    //game over screen
    erase();
    nodelay(stdscr, FALSE);
    attron(COLOR_PAIR(6));
    mvprintw(HEIGHT / 2 - 5, WIDTH / 2 - 9, "GAME OVER");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 9, "SCORE:");
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 2, "%d", score);
    wgetch(win);
    return 0;
}
