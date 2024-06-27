#include "sort_min.h"
#include <stdlib.h>
#include "struct.h"
#include "my_lib.h"

void sort_min(struct text* text){
    for (int i = 0; i < text->count_sentence; i++) {
        if (text->sentence[i].count_dates != 0) {
            qsort(text->sentence[i].dates, text->sentence[i].count_dates, sizeof(int*), compare_in_sentence);
        }
    }
    qsort(text->sentence, text->count_sentence, sizeof(struct sentence),(int (*)(const void *, const void *)) (struct sentence(*)(const void *, const void *)) compare_in_text);
}