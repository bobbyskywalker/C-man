#include "curses.h"
#include "gamefiles.h"

void printhelp(int x, int y) {
    char arrows[] = {"Use ARROWKEYS to move"};
    char orbs[] = {"Collect orbs to gain points!"};
    char ghosts[] = {"Avoid ghosts! If you lose 3 lives, game over :(("};
    char powerorbs[] = {"Power orbs let you eat ghosts! Eat a ghost for 100 bonus points!"};
    init_pair(69, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(69));
    mvprintw(7, x / 2, arrows);
    mvprintw(9, x / 2, orbs);
    mvprintw(11, x / 2, ghosts);
    mvprintw(13, x / 2, powerorbs);
    attroff(COLOR_PAIR(69));
}

void printmenu() {
    const char opt1[] = "Play";
    const char opt2[] = "Help";
    const char opt3[] = "High Scores";
    const char opt4[] = "Exit";
    const char title[] = "-------- C-MAN ---------";
    bool exit = false, help = false;
    int selection;
    int highlighted = 1, minmenu = 1, maxmenu = 4;
    //start
    WINDOW *win = initscr();
    nodelay(stdscr, FALSE);
    int x, y;
    char welcome[] = "press space...";
    getmaxyx(stdscr, x, y);
    mvprintw(x / 2, (y / 2) - (sizeof(welcome) / 2), welcome);
    noecho();
    do {
        curs_set(0);
        //get a char for menu movement
        selection = wgetch(win);
        clear();
        if (selection == 'a' && highlighted != minmenu) {
            highlighted--;
        } else if (selection == 'z' && highlighted != maxmenu) {
            highlighted++;
        }
        if (selection == 10) {
            switch (highlighted) {
                case 1:
                    gameplay(win);
                    break;
                case 2:
                    while (1) {
                        erase();
                        //arrow movement, collecting, scoring, show characters
                        printhelp(x, y);
                        if (getch()) {
                            erase();
                            break;
                        }
                    }
                    break;
                case 3:
                    //preview highscores
                    break;
                case 4:
                    exit = true;
                    break;
            }
        }
        switch (highlighted) {
            case 1:
                start_color(); //2
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron(COLOR_PAIR(1)); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                mvprintw((x / 2), (y / 2) - (sizeof(opt1) / 2), "%s\n", opt4);
                break;
            case 2:
                start_color();
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron(COLOR_PAIR(1)); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                mvprintw((x / 2), (y / 2) - (sizeof(opt1) / 2), "%s\n", opt4);
                break;
            case 3:
                start_color();
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron(COLOR_PAIR(1)); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
                mvprintw((x / 2), (y / 2) - (sizeof(opt1) / 2), "%s\n", opt4);
                break;
            case 4:
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                init_pair(1, COLOR_WHITE, COLOR_BLUE);
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw((x / 2), (y / 2) - (sizeof(opt1) / 2), "%s\n", opt4);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
        }
        init_pair(56, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(56));
        mvprintw(5, (y / 2) - 12, title);
        attroff(COLOR_PAIR(56));
    } while ((exit != true));
    wgetch(win);
    endwin();
}