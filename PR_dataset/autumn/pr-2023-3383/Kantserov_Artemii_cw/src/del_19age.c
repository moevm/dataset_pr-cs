#include "del_19age.h"
#include "struct.h"

void del_19age(struct text *text) {
    for (int i = 0; i < text->count_sentence; i++) {
        for (int j = 0; j < text->sentence[i].count_dates; j++) {
            if (1800 <= text->sentence[i].dates[j][2] && 1900 > text->sentence[i].dates[j][2]) {
                text->sentence[i].print = 0;
                break;
            }
        }
    }
}