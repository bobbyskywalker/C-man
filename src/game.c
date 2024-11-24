#include "../headers/pacman.h"

int gameplay(WINDOW *win) {
    if (stdscr == NULL) {
        printf("Error: stdscr is NULL\n");
        return -1;
    }
    //initialize screen
    erase();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    start_color();

    // init colors
    init_pair(69, COLOR_GREEN, COLOR_BLACK);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(99, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(100, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);

    // hud
    int score = 1;
    int lives = 3;
    int time = 60;
    int timer = 0;
    char lifestr[] = "LIVES";
    char timestr[] = "TIME:";

    //pac-man variables
    vec pacman = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    vec dir = {1, 0};

    //berry array and copy for reset
    berrytrack berrytracker[BERRY_TRACKER_ROWS][BERRY_TRACKER_COLS];
    for (int i = 0; i < BERRY_TRACKER_ROWS; i++) {
        for (int j = 0; j < BERRY_TRACKER_COLS; j++) {
            berrytracker[i][j].iseaten = false;
        }
    }
    berrytrack berrytracker_copy[BERRY_TRACKER_ROWS][BERRY_TRACKER_COLS];
    memcpy(berrytracker_copy, berrytracker, sizeof(berrytracker));

    //orb variables
    vec orb = {30, 15};
    int orb_time = 150;
    bool orb_effect = false;

    // ghost list init
    ghosts *head = NULL;
    vec *gh[4];
    vec *gdir[4];
    int ghosts_start_pos[4][2] = {
        {SCREEN_WIDTH / 4, 5},
        {SCREEN_WIDTH * 3 / 4, 5},
        {SCREEN_WIDTH / 4, 25},
        {SCREEN_WIDTH * 3 / 4, 25} 
    };
    for (int i = 0; i < 4; i++) 
    {
        gh[i] = malloc(sizeof(vec));
        gh[i]->x = ghosts_start_pos[i][0];
        gh[i]->y = ghosts_start_pos[i][1];

        gdir[i] = malloc(sizeof(vec));
        gdir[i]->x = 1;
        gdir[i]->y = 0; 
        head = add_ghost(head, gh[i], gdir[i]);
    }

    int exit = 0;

    //game loop
    while (exit != 27) {
        clock_t start_time = clock();
        
        int pressed = wgetch(win);
        vec last_empty_pac = {pacman.x, pacman.y};

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
            default:
                break;
        }
        pacman.x += dir.x;
        pacman.y += dir.y;

        // collisions
        chtype bdcheck = get_char_at(stdscr, pacman.y, pacman.x);
        char character = bdcheck & A_CHARTEXT;

        // ghost collision
        if (character == '#' && !orb_effect)
            lives--;
        else if (character == '#' && orb_effect)
        {
            score += 100;
            head = remove_ghost(head, pacman.x, pacman.y);
        }

        // border collision: pacman
        if (character == '-' || character == '|')
            pacman.x = last_empty_pac.x;
        if (character == '-' || character == '|')
            pacman.y = last_empty_pac.y;
        else if (pacman.y == 3)
            pacman.y++;
        else if (pacman.y == 27)
            pacman.y--;
            
        // berry consumption mechanism, score update
        if (character == '.') {
            berrytracker[pacman.y - BERRY_START_ROW][pacman.x - BERRY_START_COL].iseaten = true;
            score++;
        }

        // power orb consumption
        if (character == '@')
            orb_effect = true;

        // check for game over conditions
        if (lives == 0 || time == 0)
            break;

        erase();

        //add map
        draw_borders();
        spawn_berries(berrytracker);

        //power orb spawn / activate orb effect
        update_orb(&orb, &orb_time, &orb_effect);

        //add pac
        attron(COLOR_PAIR(1));
        mvaddch(pacman.y, pacman.x, 'C');
        attroff(COLOR_PAIR(1));

        //add ghosts
        if (orb_effect)
            attron(COLOR_PAIR(100));
        else
            attron(COLOR_PAIR(99));       
        ghosts *current = head;
        while (current != NULL) {
            mvaddch(current->ghost->y, current->ghost->x, '#');
            move_ghost(current);
            current = current->next;
        }

        //upper screen signs
        attron(COLOR_PAIR(4));
        mvprintw(2, 95 - 6, "SCORE:");
        mvprintw(2, 95, "%d", score);
        attron(COLOR_PAIR(6));
        mvprintw(2, SCREEN_WIDTH / 2 - sizeof(lifestr) + 10, "LIVES: %d", lives);
        mvprintw(2, SCREEN_WIDTH / 2 - sizeof(timestr) - 5, "TIME: %d", time);

        // timing control
        timer++;
        if (timer >= FPS)
        {
            time--;
            timer = 0;
        }
        // fps control
        clock_t end_time = clock();
        long elapsed_time_us = (end_time - start_time) * 1000000 / CLOCKS_PER_SEC;
        if (elapsed_time_us < FRAME_DURATION)
            usleep(FRAME_DURATION - elapsed_time_us);
    }
    // berry board reset after game
    memcpy(berrytracker, berrytracker_copy, sizeof(berrytracker));

    // ghost memo free
    if (head != NULL)
        free_ghosts(head);
    for (int i = 0; i < 4; i++) {
        free(gh[i]);
        free(gdir[i]);
    }

    game_over_screen(win, score);
    erase();
    endwin();
    refresh();
    return 0;
}
