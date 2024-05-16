#include <stdio.h>
#include <unistd.h>
#include "curses.h"
#include "gamefiles.h"

#define HEIGHT 30
#define WIDTH 120


//TODO: function to create borders, and borders inside the map, update the collision mechanism
// 2. fruit spawning and collecting (adding to the score)
typedef struct vector{
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
    vec pacman = {1, 1};
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
            if(pacman.x == 0){
                pacman.x++;
            }else if(pacman.x == WIDTH){
                pacman.x--;
            }
            if(pacman.y == 0){
                pacman.y++;
            }else if(pacman.y == HEIGHT) {
                pacman.y--;
            }
            erase();
            start_color(); //2
            init_pair(1, COLOR_YELLOW, COLOR_BLACK); //3
            attron(COLOR_PAIR(1)); //4
            mvaddch(pacman.y, pacman.x, 'C');
            usleep(40000);
        }
        getch();
        return 0;
    }