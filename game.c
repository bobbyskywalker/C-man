#include <unistd.h>
#include <stdlib.h>
#include "curses.h"
#include "gamefiles.h"

#define HEIGHT 30
#define WIDTH 120

chtype get_char_at(WINDOW *win, int y, int x) {
    wmove(win, y, x);
    return winch(win);
}

int gameplay(WINDOW *win) {
    //initialize screen
    int screenwidth, screenheight;
    erase();
    int score = 0;
    int lives = 3;
    int time = 90;
    int time_iterations = 0;
    char lifestr[] = "<3:";
    char timestr[] = "TIME:";
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
    vec *ghost4 = malloc(2 * sizeof(int));
    ghost1->x = 25;
    ghost1->y = 6;
    ghost2->x = 90;
    ghost2->y = 8;
    ghost3->x = 25;
    ghost3->y = 25;
    ghost4->x = 90;
    ghost4->y = 25;
    vec *gdir1 = malloc(2 * sizeof(int));
    gdir1->x = 1;
    gdir1->y = 0;
    vec *gdir2 = malloc(2 * sizeof(int));
    gdir2->x = 1;
    gdir2->y = 0;
    vec *gdir3 = malloc(2 * sizeof(int));
    gdir3->x = 0;
    gdir3->y = 1;
    vec *gdir4 = malloc(2 * sizeof(int));
    gdir4->x = 0;
    gdir4->y = 1;
    //true = alive
    bool ghost_status[4] = {true, true, true, true};

    //berry array and copy for reset
    berrytrack berrytracker[35][104];
    berrytrack berrytracker_copy[35][104];
    memcpy(berrytracker_copy, berrytracker, sizeof(berrytracker));

    //orb variables
    vec orb = {30, 15};
    int orb_time = 150;
    bool orb_effect = false;

    int exit = 0;
    bool *hit = false;
    //game loop
    while (exit != 27) {
        curs_set(0);
        noecho();
        int pressed = wgetch(win);
        vec last_empty_pac = {pacman.x, pacman.y};
        //ghost collision, -1 life or eat a ghost
        chtype killcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char killchar = killcheck & A_CHARTEXT;
        if (killchar == '#') hit = (bool *) true;
        if (hit == true && orb_effect == false) {
            lives--;
            hit = false;
        } else if (hit == true && orb_effect == true) {
            pacman.x == ghost1->x && pacman.y == ghost1->y ? (ghost_status[0] = false), score += 100 : 1;
            pacman.x == ghost2->x && pacman.y == ghost2->y ? (ghost_status[1] = false), score += 100 : 1;
            pacman.x == ghost3->x && pacman.y == ghost3->y ? (ghost_status[2] = false), score += 100 : 1;
            pacman.x == ghost4->x && pacman.y == ghost4->y ? (ghost_status[3] = false), score += 100 : 1;
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
                erase();
                break;
        }
        pacman.x += dir.x;
        pacman.y += dir.y;


        //border collision: pacman
        chtype bdcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char character = bdcheck & A_CHARTEXT;

        if (character == '_' || character == '|') {
            pacman.x = last_empty_pac.x;
        }
        if (character == '_' || character == '|') {
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

        //power orb consumption
        if (character == '@') {
            orb_effect = true;
        }

        //ghost movement
        ghost1 = move_ghost(ghost1, gdir1, hit);
        ghost2 = move_ghost(ghost2, gdir2, hit);
        ghost3 = move_ghost(ghost3, gdir3, hit);
        ghost4 = move_ghost(ghost4, gdir4, hit);

        //death
        if (lives == 0 || time == 0) {
            break;
        }

        erase();
        start_color();

        //add map
        draw_borders();
        spawn_berries(berrytracker);

        //power orb spawn/ activate effect
        if (orb_effect == true) {
            orb.x = rand() % (99 - 21 + 1) + 21;
            orb.y = rand() % (27 - 4 + 1) + 4;
            bdcheck = get_char_at(stdscr, orb.y, orb.x);
            character = bdcheck & A_CHARTEXT;
            if (character == '_') {
                orb.y = rand() % (27 - 4 + 1) + 4;
                orb.x = rand() % (99 - 21 + 1) + 21;
            } else if (character == '|') {
                orb.y = rand() % (27 - 4 + 1) + 4;
                orb.x = rand() % (99 - 21 + 1) + 21;
            }
            orb_time--;
        } else {
            init_pair(69, COLOR_GREEN, COLOR_BLACK);
            attron(COLOR_PAIR(69));
            mvaddch(orb.y, orb.x, '@');
            attroff(COLOR_PAIR(69));
        }
        if (orb_time == 0) {
            orb_time = 150;
            orb_effect = false;
        }

        //add pac
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvaddch(pacman.y, pacman.x, 'C');
        attroff(COLOR_PAIR(1));

        //add ghosts (change color if orb is active)
        if (orb_effect == false) {
            init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
            attron(COLOR_PAIR(5));
        } else {
            init_pair(99, COLOR_MAGENTA, COLOR_WHITE);
        }
        if (ghost_status[0] != false) {
            mvaddch(ghost1->y, ghost1->x, '#');
        }
        if (ghost_status[1] != false) {
            mvaddstr(ghost2->y, ghost2->x, "#");
        }
        if (ghost_status[2] != false) {
            mvaddch(ghost3->y, ghost3->x, '#');
        }
        if (ghost_status[3] != false) {
            mvaddch(ghost4->y, ghost4->x, '#');
        }
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(99));

        //upper screen signs
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(2, 95 - 6, "SCORE:");
        mvprintw(2, 95, "%d", score);
        init_pair(6, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(6));
        mvprintw(2, WIDTH / 2 - sizeof(lifestr) + 10, lifestr);
        mvprintw(2, WIDTH / 2 - sizeof(lifestr) + 13, "%d", lives);
        mvprintw(2, WIDTH / 2 - sizeof(timestr) - 5, timestr);
        mvprintw(2, WIDTH / 2 - sizeof(timestr) + 3, "%d", time);
        //time passing
        if (time_iterations == 14) {
            time--;
            time_iterations = 0;
        }
        time_iterations++;
        attroff(COLOR_PAIR(6));
        usleep(65000);
    }
    //board reset after game
    memcpy(berrytracker, berrytracker_copy, sizeof(berrytracker));
    //game over screen
    erase();
    nodelay(stdscr, FALSE);
    attron(COLOR_PAIR(6));
    mvprintw(HEIGHT / 2 - 5, WIDTH / 2 - 9, "GAME OVER");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 9, "SCORE:");
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 2, "%d", score);
    attroff(COLOR_PAIR(1));
    mvprintw(1, 1, "press esc to exit");
    attron(COLOR_PAIR(5));
    mvprintw(HEIGHT / 2 + 8, WIDTH / 2 - 9, "Save your score? y/n");
    attroff(COLOR_PAIR(5));
    int exit_button;
    while (exit_button != 27 && exit_button != 'n') {
        if (exit_button == 'y') {
            erase();
            save_score(score, win);
            break;
        }
        exit_button = wgetch(win);
    }
    erase();
    return 0;
}
