#include "../headers/pacman.h"

#define HEIGHT 30
#define WIDTH 120

int gameplay(WINDOW *win) {
    if (stdscr == NULL) {
        printf("Error: stdscr is NULL\n");
        return -1;
    }
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

    // game timer setup
    float accumulated_time = 0;  // Accumulate elapsed time in seconds
    const float seconds_per_update = 1.0f; // Decrement `time` every 1 second

    //pac-man variables
    vec pacman = {WIDTH / 2, HEIGHT / 2};
    vec dir = {1, 0};

    //berry array and copy for reset
    berrytrack berrytracker[35][104];
    berrytrack berrytracker_copy[35][104];
    memcpy(berrytracker_copy, berrytracker, sizeof(berrytracker));

    //orb variables
    vec orb = {30, 15};
    int orb_time = 150;
    bool orb_effect = false;

    ghosts *head = NULL;
    int ghosts_start_pos[4][2] = {
        {WIDTH / 4, 5},  // top-left ghost
        {WIDTH * 3 / 4, 5},  // top-right ghost
        {WIDTH / 4, 25},  // bottom-left ghost
        {WIDTH * 3 / 4, 25}  // bottom-right ghost
    };
    for (int i = 0; i < 4; i++) 
    {
        vec *gh = malloc(sizeof(vec));
        if (!gh) exit(EXIT_FAILURE);
        gh->x = ghosts_start_pos[i][0];
        gh->y = ghosts_start_pos[i][1];

        vec *gdir = malloc(sizeof(vec));
        if (!gdir) exit(EXIT_FAILURE);
        gdir->x = 1;
        gdir->y = 0; 
        head = add_ghost(head, gh, gdir);
    }

    int exit = 0;

    //game loop
    while (exit != 27) {
        clock_t start_time = clock();
        curs_set(0);
        noecho();
        int pressed = wgetch(win);
        vec last_empty_pac = {pacman.x, pacman.y};
        //ghost collision, -1 life or eat a ghost
        chtype killcheck = get_char_at(stdscr, pacman.y, pacman.x);
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

        // ghost collision
        if (character == '#' && !orb_effect)
            lives--;
        else if (character == '#' && orb_effect)
        {
            score += 100;
            head = remove_ghost(head, pacman.x, pacman.y);
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

        // Check for game over conditions
        if (lives == 0 || time == 0) {
            break;
        }
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


        //add ghosts
        init_pair(99, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(100, COLOR_WHITE, COLOR_BLACK);
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

        // TODO: to fix 
        // Timing control / FPS
        clock_t end_time = clock();
        float frame_time_sec = (float)(end_time - start_time) / CLOCKS_PER_SEC;
        accumulated_time += frame_time_sec;

        // Decrement time every second
        if (accumulated_time >= seconds_per_update) {
            time--;
            accumulated_time -= seconds_per_update; // Ensure no time is lost
        }
        // Control frame rate
        long elapsed_time_us = (end_time - start_time) * 1000000 / CLOCKS_PER_SEC;

        if (elapsed_time_us < FRAME_DURATION) {
            usleep(FRAME_DURATION - elapsed_time_us);
        }
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
    int exit_button;
    erase();
    return 0;
}
