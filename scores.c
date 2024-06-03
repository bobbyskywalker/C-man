#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "curses.h"
#include "gamefiles.h"

//TODO: print entered initials, sort score function, print the sorted scores in "highscores" option menu
void save_score(int score, WINDOW *win){
    char initials[4];
    char *scorestr = calloc(7 + 3, sizeof(char));
    sprintf(scorestr, "%d", score);
    FILE *score_fileptr;
    score_fileptr = fopen("C:\\Users\\olek\\CLionProjects\\pacmangame\\cmake-build-debug\\scores.txt", "r");
    if(score_fileptr == 0){
        score_fileptr = fopen("C:\\Users\\olek\\CLionProjects\\pacmangame\\cmake-build-debug\\scores.txt", "w");
        for(int i = 0; i < 3; i++){
            initials[i] = wgetch(win);
        }
        initials[3] = '\0';
        scorestr[strlen(scorestr)] = ',';
        strcat(scorestr, initials);
        scorestr[strlen(scorestr)] = ',';
        scorestr[strlen(scorestr)] = '\0';
        fprintf(score_fileptr, "%s", scorestr);
    }else{
        score_fileptr = fopen("C:\\Users\\olek\\CLionProjects\\pacmangame\\cmake-build-debug\\scores.txt", "a");
        for(int i = 0; i < 3; i++){
            initials[i] = wgetch(win);
        }
        initials[3] = '\0';
        scorestr[strlen(scorestr)] = ',';
        strcat(scorestr, initials);
        scorestr[strlen(scorestr)] = ',';
        scorestr[strlen(scorestr)] = '\0';
        fprintf(score_fileptr, "%s", scorestr);
    }
    fclose(score_fileptr);

}
