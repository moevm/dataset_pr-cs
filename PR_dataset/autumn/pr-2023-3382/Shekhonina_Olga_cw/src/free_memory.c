#include "free_memory.h"

void free_memory(Text* text) {
    int len = text->count_sent;
    for(int i = 0; i<len; i++) {
        free(text->pr_sent[i]->sentence);
        free(text->pr_sent[i]);
    }
    for(int i = 0; i<text->slash_dates->size; i++) {
        free(text->slash_dates->arr[i]->day);
        free(text->slash_dates->arr[i]->month);
        free(text->slash_dates->arr[i]->year);
        free(text->slash_dates->arr[i]);
    }
    for(int i = 0; i<text->dash_dates->size; i++) {
        free(text->dash_dates->arr[i]->day);
        free(text->dash_dates->arr[i]->month);
        free(text->dash_dates->arr[i]->year);
        free(text->dash_dates->arr[i]);
    }
    for(int i = 0; i<text->space_dates->size; i++) {
        free(text->space_dates->arr[i]->day);
        free(text->space_dates->arr[i]->month);
        free(text->space_dates->arr[i]->year);
        free(text->space_dates->arr[i]);
    }
    free(text);
}
