#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "curses.h"
#include "gamefiles.h"
#include <string.h>

#define HEIGHT 30
#define WIDTH 120

//TODO: printing highscores with empty file

//extractions
char **extract_initials(char *scoring) {
    char *buff = calloc(3 + 1, sizeof(char));
    char **initials = calloc(strlen(scoring), 4 * sizeof(char));
    int len = (int) strlen(scoring);
    bool isinit = false;
    int size = 0;
    for (int i = 0, initials_index = 0, buff_index = 0; i < len; i++) {
        if (scoring[i] == ',') {
            isinit = !isinit;
            continue;
        }
        if (scoring[i] == ';') {
            isinit = !isinit;
            buff[buff_index] = '\0';
            initials[initials_index] = calloc(4, sizeof(char));
            strcpy(initials[initials_index++], buff);
            memset(buff, 0, 4);
            buff_index = 0;
            size = initials_index;
            continue;
        }
        if (isinit && buff_index < 3) { //buffer overflow prevention
            buff[buff_index++] = scoring[i];
        }
    }
    initials[size] = NULL;
    free(buff);
    return initials;
}

int *extract_scores(char *scoring) {
    char *buff = calloc(4 + 1, sizeof(int));
    int *scores = calloc(strlen(scoring), sizeof(int));
    int len = strlen(scoring);
    int element, elementlen = 0, size = 0;
    bool is_score = true;

    for (int i = 0, scores_index = 0, buff_index = 0; i < len; i++) {
        if (scoring[i] == ',') {
            is_score = !is_score;
            continue;
        }
        if (scoring[i] == ';') {
            is_score = !is_score;
            buff[elementlen] = '\0';
            element = atoi(buff);
            scores[scores_index++] = element;
            buff_index = 0, elementlen = 0;
            memset(buff, 0, elementlen);
            size = scores_index;
            continue;
        }
        if (is_score) {
            buff[buff_index++] = scoring[i];
            elementlen++;
        }
    }
    scoring[size] = '\0';
    free(buff);
    return scores;
}

//save the score to a file
void save_score(int score, WINDOW *win) {
    char initials[4];

    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char filename[] = "\\scores.txt";
    strcat(path, filename);
    path[strlen(path)] = '\0';

    char *scorestr = calloc(7 + 3, sizeof(char));
    sprintf(scorestr, "%d", score);
    FILE *score_fileptr;
    score_fileptr = fopen(path, "r");
    if (score_fileptr == 0) {
        score_fileptr = fopen(path, "w");
        for (int i = 0; i < 3; i++) {
            erase();
            mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 9, "ENTER 3 INITIALS:");
            initials[i] = wgetch(win);
            mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "%s", initials);
        }
        initials[3] = '\0';
        scorestr[strlen(scorestr)] = ',';
        strcat(scorestr, initials);
        scorestr[strlen(scorestr)] = ';';
        scorestr[strlen(scorestr)] = '\0';
        fprintf(score_fileptr, "%s", scorestr);
    } else {
        score_fileptr = fopen(path, "a");
        for (int i = 0; i < 3; i++) {
            erase();
            mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 9, "ENTER 3 INITIALS:");
            initials[i] = wgetch(win);
            mvprintw(HEIGHT / 2, WIDTH / 2 - 9, "%s", initials);
        }
        initials[3] = '\0';
        scorestr[strlen(scorestr)] = ',';
        strcat(scorestr, initials);
        scorestr[strlen(scorestr)] = ';';
        scorestr[strlen(scorestr)] = '\0';
        fprintf(score_fileptr, "%s", scorestr);
        fclose(score_fileptr);
    }
    wgetch(win);
}

//read the score
FILE *read_score(WINDOW *win) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char filename[] = "\\scores.txt";
    strcat(path, filename);
    path[strlen(path)] = '\0';
    FILE *score_fileptr;
    score_fileptr = fopen(path, "r");
    return score_fileptr;
}


//sorting by highscores
int comparator(const void *x, const void *y) {
    int s1 = ((struct scoreblock *) x)->score;
    int s2 = ((struct scoreblock *) y)->score;
    return s2 - s1;
}

scoreblock *sort_score(FILE *score_fileptr) {
    char *scoring = calloc(10000, sizeof(char)); // Assuming 1000 chars is enough to hold file content
    char **initials;
    int *scores;
    size_t total_len = 0;
    int size = 0;
    while (fgets(scoring + total_len, 10000 - total_len, score_fileptr)) {
        total_len = strlen(scoring);
    }
    scoreblock *score_elements = malloc(total_len / 6);
    initials = extract_initials(scoring);
    scores = extract_scores(scoring);
    //copy contents into struct array
    for (int i = 0; initials[i] != NULL; i++) {
        strcpy(score_elements[i].initials, initials[i]);
        size = i;
    }
    for (int i = 0; scores[i] != '\0'; i++) {
        score_elements[i].score = scores[i];
    }
    //sort the array
    qsort(score_elements, size + 1, sizeof(scoreblock), comparator);
    //global variable
    return score_elements;
}

//print score in menu
void print_score(scoreblock *sorted) {
    //print top 10 scores
    init_pair(47, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(47));
    int place = 1;
    mvprintw(8, 50, "HIGH SCORES:");
    for (int i = 0, r = 10, c = 50; i < 10; i++, r++) {
        if (i != 9) {
            mvprintw(r, c - 3, "%d", place++);
        } else {
            mvprintw(r, c - 4, "%d", place++);
        }
        mvprintw(r, c - 2, ".");
        mvprintw(r, c, "%s", sorted[i].initials);
        mvprintw(r, c + 4, " %d", sorted[i].score);
    }
    attroff(COLOR_PAIR(47));
}




