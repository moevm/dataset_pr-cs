#include "my_lib.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void free_memory_in(struct text* text){
    for (int i = 0; i < text->count_sentence; i++) {
        free(text->sentence[i].str);
    }
    free(text->sentence);
    free(text);
}

void free_memory(struct text* text) {
    for (int i = 0; i < text->count_sentence; i++) {
        free(text->sentence[i].str);
        for (int j = 0; j < text->sentence[i].count_dates; j++) {
            free(text->sentence[i].dates[j]);
        }
        if (text->sentence[i].count_dates == 0) {
            free(text->sentence[i].dates[0]);
        }
        free(text->sentence[i].dates);
    }
    free(text->sentence);
    free(text);
}
int del_repeat(struct text* text, struct sentence* sentence) {
    for (int i = 0; i < text->count_sentence; i++) {
        int j = 0;
        int fl = 0;
        while (text->sentence[i].str[j] != '\0' && sentence->str[j] != '\0') {
            if (text->sentence[i].str[j] != sentence->str[j]) {
                fl ++;
                break;
            }
            j++;
        }
        if (fl == 0) {
            return 0;
        }
        fl = 0;
    }
    return 1;
}

void processing_text(struct text* text) {
    for (int i = 0; i < text->count_sentence; i++) {
        processing_sentence(&text->sentence[i]);
    }
}
int compare_in_text(const struct sentence *f, const struct sentence *s ) {
    for (int i = 2; i >= 0; i--) {
        if (f->dates[0][i] < s->dates[0][i]) return -1;
        if (f->dates[0][i] > s->dates[0][i]) return 1;
    }
    return 0;
}

int compare_in_sentence(const void* a, const void* b) {
    const int *f = *(const int **)a;
    const int *s = *(const int **)b;
    for (int i = 2; i >= 0  ; i--) {
        if (f[i] < s[i]) return -1;
        if (f[i] > s[i]) return 1;
    }
    return 0;
}

void processing_sentence(struct sentence *sentence) {
    char* str = strdup(sentence->str);
    int max_count = 1;
    sentence->dates = (int**)malloc(max_count * sizeof(int*));
    if (sentence->dates == NULL) {
        printf("Error: не удалось распределить память.");
        exit(1);
    }
    sentence->dates[0] = calloc(3, sizeof(int));
    if (sentence->dates == NULL) {
        printf("Error: не удалось распределить память.");
        exit(1);
    }
    int* date;
    sentence->count_dates = 0;
    char* token = strtok(str, " .");
    while (token != NULL) {
        if ((date = correct_date(token)) == NULL) {
            token = strtok(NULL, " .");
//            sentence->print = 0;  // чтобы не выводить предложения без дат.

//            printf("Error: не корректный ввод дат."); // чтобы выдавать ошибку при вводе текста в функциях 1, 2, 3, 4.
//            exit(1);
            continue;
        }
        sentence->print = 1;
        max_count++;
        sentence->dates = realloc(sentence->dates, max_count * sizeof(int*));
        if (sentence->dates == NULL) {
            printf("Error: не удалось перераспределить память.");
            exit(1);
        }
        if (sentence->dates[sentence->count_dates] == NULL) {
            printf("Error: не удалось перераспределить память.");
            exit(1);
        }
        sentence->dates[sentence->count_dates] = date;
        sentence->count_dates++;
        sentence->dates[sentence->count_dates] = malloc(3*sizeof(int));
        token = strtok(NULL, " .");
    }
}

int* correct_date(char* token) {
    int *date = malloc(sizeof(int)*3);
    if (sscanf(token, "%d/%d/%d", &date[0], &date[1], &date[2]) == 3 && date[2] >= 1 && date[2] < 10000 && strlen(token) == 10) {
        if (( date[1] == 1 || date[1] == 3 || date[1] == 5 || date[1] == 7 || date[1] == 8 || date[1] == 10 || date[1] == 12) && date[0] > 0 && date[0] <= 31) {
            return date;
        }
        if ((date[1] == 4 || date[1] == 6 || date[1] == 9 || date[1] == 11) && date[0] > 0 && date[0] <= 30) {
            return date;
        }
        if (date[1] == 2 && ((((date[2] % 4 == 0 && date[2] % 100 != 0) || (date[2] % 4 == 0 && date[2] % 400 == 0 )) && date[0] > 0 && date[0] <= 29) || (((date[2] % 4 != 0) || (date[2] % 4 == 0 && date[2] % 400 != 0)) && date[0] > 0 && date[0] <= 28))) {
            return date;
        }
    }
    return NULL;
}