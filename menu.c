#include <stdio.h>
#include <unistd.h>
#include "curses.h"

//bool maybe? to verify which mode are we in OR just put the game inside

void printmenu(){
    const char opt1[] = "Play";
    const char opt2[] = "Help";
    const char opt3[] = "Exit";
    int selection;
    int highlighted = 1, minmenu = 1, maxmenu = 3;
    //start
    initscr();
    int x,y;
    char welcome[] = "press space...";
    getmaxyx(stdscr, x, y);
    mvprintw(x / 2, (y / 2) - (sizeof(welcome) / 2), welcome);
    noecho();
    do {
        //get a char for menu movement
        selection = getch();
        clear();
        if(selection == 'a' && highlighted != minmenu){
            highlighted--;
        }else if(selection == 'z' && highlighted != maxmenu){
            highlighted++;
        }
        if(selection == 10){
            switch (highlighted) {
                case 1:
                    printw("the game will be here :)");
                    break;
                case 2:
                    printw("manual will appear here");
                    break;
                case 3:
                    printw("naura");
                    endwin();
                    //return 0
            }
        }
        //color pairs: 1 is currently highlighted, 2 is other selections
        switch (highlighted) {
            case 1:
                start_color(); //2
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron(COLOR_PAIR( 1 ) ); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                attroff( COLOR_PAIR( 1 ) );
                attroff(A_BOLD);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                break;
            case 2:
                start_color();
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron(COLOR_PAIR( 1 ) ); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                attroff(COLOR_PAIR( 1 ) );
                attroff(A_BOLD);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                break;
            case 3:
                start_color();
                mvprintw((x / 2) - 3, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt1);
                mvprintw((x / 2) - 2, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt2);
                init_pair(1, COLOR_WHITE, COLOR_BLUE); //3
                attron( COLOR_PAIR( 1 ) ); //4
                attron(A_BOLD);
                mvprintw((x / 2) - 1, (y / 2) - (sizeof(opt1) / 2), "%s\n", opt3);
                attroff(COLOR_PAIR( 1 ) );
                attroff(A_BOLD);
                break;
        }
    } while(highlighted != 4 && selection != 10);
//    clear();
//    printw("gameon");
    getch();
    endwin();
}
