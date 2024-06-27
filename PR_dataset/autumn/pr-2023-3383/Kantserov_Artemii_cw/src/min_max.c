#include "min_max.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "my_lib.h"

void min_max(struct text* text) {
    for (int i = 0; i < text->count_sentence; i++) {
        if (text->sentence[i].count_dates != 0) { // text->sentence[i].print != 0 если выводим не все предложения.
            qsort(text->sentence[i].dates, text->sentence[i].count_dates, sizeof(int*), compare_in_sentence);
            text->sentence[i].str = realloc(text->sentence[i].str, strlen(text->sentence[i].str)+30);
            char* str = malloc(sizeof(char) * 30);
            sprintf(str, "  %d/%d/%d %d/%d/%d", text->sentence[i].dates[0][0], text->sentence[i].dates[0][1], text->sentence[i].dates[0][2], text->sentence[i].dates[text->sentence[i].count_dates-1][0], text->sentence[i].dates[text->sentence[i].count_dates-1][1], text->sentence[i].dates[text->sentence[i].count_dates-1][2]);
            text->sentence[i].str = strcat(text->sentence[i].str, str);
            free(str);
        }
    }
}