#include <unistd.h>
#include "curses.h"
#include "gamefiles.h"

#define HEIGHT 30
#define WIDTH 120

//chtype get_char_at(WINDOW *win, int y, int x) {
//    wmove(win, y, x);
//    return winch(win);
//}


//TODO: inside of the map border collision, introduce some bools maybe
//fruit collecting mechanism + score counter


typedef struct vector {
    int x;
    int y;
} vec;

int gameplay() {
    //initialize screen
    int screenwidth, screenheight;
    WINDOW *win = initscr();
    getmaxyx(stdscr, screenheight, screenwidth);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    //pac-man
    vec pacman = {WIDTH / 2, HEIGHT / 2};
    vec dir = {1, 0};
    int exit = 0;

    //game loop
    while (exit != 27) {
        curs_set(0);
        int pressed = wgetch(win);
        //key reaction
        switch (pressed) {
            case KEY_LEFT:
                dir.x = -1;
                dir.y = 0;
                wall = true;
                break;
            case KEY_RIGHT:
                dir.x = 1;
                dir.y = 0;
                wall = true;
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
//        chtype bdcheck = get_char_at(stdscr, pacman.y, pacman.x);
//        char character = bdcheck & A_CHARTEXT;

        if (pacman.x == 20) {
            pacman.x++;
        } else if (pacman.x == 100) {
            pacman.x--;
        }
        if (pacman.y == 3) {
            pacman.y++;
        } else if (pacman.y == 27) {
            pacman.y--;
        }
        erase();
        start_color();
        //add map
       draw_borders();
        //add pac
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(1));

        mvaddch(pacman.y, pacman.x, 'C');
        attroff(COLOR_PAIR(1));
        usleep(50000);
    }
    getch();
    return 0;
}
