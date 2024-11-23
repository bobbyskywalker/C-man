#include "curses.h"
#include "../headers/pacman.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

void print_help(int x, int y) {
    char arrows[] = {"Use ARROWKEYS to move"};
    char orbs[] = {"Collect orbs to gain points!"};
    char ghosts[] = {"Avoid ghosts! If you lose 3 lives, game over :(("};
    char powerorbs[] = {"Power orbs let you eat ghosts! Eat a ghost for 100 bonus points!"};
    init_pair(69, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(69));
    mvprintw(7, y / 2 - strlen(arrows) / 2, arrows);
    mvprintw(9, y / 2 - strlen(orbs) / 2, orbs);
    mvprintw(11, y / 2 - strlen(ghosts) / 2, ghosts);
    mvprintw(13, y / 2 - strlen(powerorbs) / 2, powerorbs);
    attroff(COLOR_PAIR(69));
}

void print_menu() {
    const char opt1[] = "Play";
    const char opt2[] = "Help";
    const char opt3[] = "High Scores";
    const char opt4[] = "Exit";
    const char title[] = "-------- C-MAN ---------";
    bool exit = false, first_enter = true;
    int selection;
    int highlighted = 1, minmenu = 1, maxmenu = 4;

    // Initialize the window and check for failure
    WINDOW *win = initscr();
    if (win == NULL) {
        endwin();
        return;
    }
    nodelay(stdscr, FALSE);
    keypad(win, true);
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(56, COLOR_YELLOW, COLOR_BLACK);

    int x = SCREEN_HEIGHT;
    int y = SCREEN_WIDTH;

    char welcome[] = "press space...";
    mvprintw(x / 2, y / 2 - strlen(welcome) / 2, welcome);
    do {
        selection = wgetch(win);
        clear();

        if (selection == KEY_UP && highlighted != minmenu) {
            highlighted--;
        } else if (selection == KEY_DOWN && highlighted != maxmenu) {
            highlighted++;
        }

        if (selection == 10) {
            switch (highlighted) {
                case 1:
                    first_enter = true;
                    gameplay(win);
                    break;
                case 2:
                    while (1) {
                        erase();
                        print_help(x, y);
                        if (getch()) {
                            erase();
                            break;
                        }
                    }
                    break;
                case 3:
                    break;
                case 4:
                    exit = true;
                    break;
            }
        }

        int menu_pos_x = y / 2;
        int title_pos_y = 5;

        switch (highlighted) {
            case 1:
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(x / 2 - 3, menu_pos_x - strlen(opt1) / 2, "%s", opt1);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw(x / 2 - 2, menu_pos_x - strlen(opt2) / 2, "%s", opt2);
                mvprintw(x / 2 - 1, menu_pos_x - strlen(opt3) / 2, "%s", opt3);
                mvprintw(x / 2, menu_pos_x - strlen(opt4) / 2, "%s", opt4);
                break;
            case 2:
                mvprintw(x / 2 - 3, menu_pos_x - strlen(opt1) / 2, "%s", opt1);
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(x / 2 - 2, menu_pos_x - strlen(opt2) / 2, "%s", opt2);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw(x / 2 - 1, menu_pos_x - strlen(opt3) / 2, "%s", opt3);
                mvprintw(x / 2, menu_pos_x - strlen(opt4) / 2, "%s", opt4);
                break;
            case 3:
                mvprintw(x / 2 - 3, menu_pos_x - strlen(opt1) / 2, "%s", opt1);
                mvprintw(x / 2 - 2, menu_pos_x - strlen(opt2) / 2, "%s", opt2);
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(x / 2 - 1, menu_pos_x - strlen(opt3) / 2, "%s", opt3);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw(x / 2, menu_pos_x - strlen(opt4) / 2, "%s", opt4);
                break;
            case 4:
                mvprintw(x / 2 - 3, menu_pos_x - strlen(opt1) / 2, "%s", opt1);
                mvprintw(x / 2 - 2, menu_pos_x - strlen(opt2) / 2, "%s", opt2);
                mvprintw(x / 2 - 1, menu_pos_x - strlen(opt3) / 2, "%s", opt3);
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(x / 2, menu_pos_x - strlen(opt4) / 2, "%s", opt4);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
        }
        attron(COLOR_PAIR(56));
        mvprintw(title_pos_y, menu_pos_x - strlen(title) / 2, title);
        attroff(COLOR_PAIR(56));

    } while (!exit);

    wgetch(win);
    endwin();
}
