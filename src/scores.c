#include "../headers/pacman.h"

void save_score(int score, char *initials) {
    FILE *scores = fopen("scores.txt", "a");
    if (scores == NULL) {
        printf("Error opening scores.txt\n");
        return;
    }
    fprintf(scores, "%s,%d\n", initials, score);
    fclose(scores);
}

bool get_initials(const char *prompt, int score)
{
    int prompt_y = SCREEN_HEIGHT / 2;
    int prompt_x = SCREEN_WIDTH / 2 - strlen(prompt) / 2;
    mvprintw(prompt_y, prompt_x, "%s", prompt);
    mvprintw(SCREEN_HEIGHT / 2 + 10, SCREEN_WIDTH / 2 - 20, "(press enter to confirm, then q to quit)");
    refresh();
    noecho();
    char initials[4] = {0};
    size_t len = 0;
    int c = 0;
    do {
        move(prompt_y, prompt_x + strlen(prompt) + 1 + len);
        c = getch();
        if (c == '\n' || c == EOF) { 
            break;
        }
        if (len < 3 && isalnum(c)) {
            initials[len++] = c;
            printw("%c", c);
            refresh();
        }
    } while (true);
    if (len == 3) {
        initials[3] = '\0';
        save_score(score, initials);
        return false;
    } else {
        mvprintw(SCREEN_HEIGHT / 2 + 3, SCREEN_WIDTH / 2 - strlen(prompt), "Enter exactly 3 initials\n");
        return true;
    }
}

score_block* read_scores(int *no_scores) {
    FILE *scores_file = fopen("scores.txt", "r");
    if (scores_file == NULL) {
        perror("Error opening scores.txt");
        return NULL;
    }

    fseek(scores_file, 0, SEEK_END);
    long file_size = ftell(scores_file);
    rewind(scores_file);

    if (file_size == 0) {
        fclose(scores_file);
        return NULL;
    }

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(scores_file);
        return NULL;
    }
    size_t read_size = fread(buffer, 1, file_size, scores_file);
    buffer[read_size] = '\0';

    *no_scores = 0;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n')
            (*no_scores)++;
    }

    if (no_scores == 0) {
        free(buffer);
        fclose(scores_file);
        return NULL;
    }

    score_block *scores_array = (score_block *)malloc((*no_scores + 1) * sizeof(score_block) + 1);
    if (!scores_array) {
        free(buffer);
        fclose(scores_file);
        return NULL;
    }

    int char_counter = 0;
    int score_counter = 0;
    char value[5];
    for (int i = 0; i < file_size; i++) {
        if (buffer[i] == '\n') {
            if (char_counter < 4 || char_counter > 8) {
                free(buffer);
                free(scores_array);
                fclose(scores_file);
                return NULL;
            }
            value[char_counter - 4] = '\0';
            scores_array[score_counter].score = atoi(value);
            char_counter = 0;
            score_counter++;
            continue;
        }
        if (char_counter < 3) {
            scores_array[score_counter].initials[char_counter] = buffer[i];
        } else if (char_counter > 3) {
            value[char_counter - 4] = buffer[i];
        }
        char_counter++;
    }
    if (char_counter > 0) {
        value[char_counter - 4] = '\0';
        scores_array[score_counter].score = atoi(value);
        score_counter++;
    }
    fclose(scores_file);
    free(buffer);
    return scores_array;
}
int compare_scores(const void *a, const void *b) {
    score_block *sa = (score_block *)a;
    score_block *sb = (score_block *)b;
    if (sa->score > sb->score)
        return -1;
    else if (sa->score < sb->score)
        return 1;
    else
        return 0;
}

void sort_scores(score_block *scores_array, int no_scores) {
    if (scores_array == NULL || no_scores <= 0) {
        return;
    }
    qsort(scores_array, no_scores, sizeof(score_block), compare_scores);
}

void print_scores() {
    int *no_scores = malloc(sizeof(int));
    score_block *scores_array = read_scores(no_scores);
    if (scores_array == NULL) {
        mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 10, "No scores available.\n");
        return;
    }
    sort_scores(scores_array, *no_scores);
    init_pair(55, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(55));
    mvprintw(SCREEN_HEIGHT / 2 - 7, SCREEN_WIDTH / 2 - 10, "High Scores:\n");
    attroff(COLOR_PAIR(55));
    int limit;
    if (*no_scores < 10)
        limit = *no_scores;
    else
        limit = 10;
    for (int i = 0; i < limit; i++) {
        mvprintw(10 + i, SCREEN_WIDTH / 2 - 10, "%d.%s %d\n", i + 1, scores_array[i].initials, scores_array[i].score);
    }
    free(no_scores);
    free(scores_array);
}
