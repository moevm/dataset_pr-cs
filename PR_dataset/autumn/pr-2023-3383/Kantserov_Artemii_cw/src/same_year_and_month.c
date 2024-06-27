#include "same_year_and_month.h"
#include <stdio.h>
#include <time.h>
#include "struct.h"

void same_year_and_month (struct text* text) {
    time_t tm = time(NULL);
    struct tm *TM = localtime(&tm);
    char tru_year[5], tru_month[3];
    int year, month;
    strftime(tru_month, 2, "%m", TM);
    strftime(tru_year, 4, "%Y", TM);
    sscanf(tru_month, "%d", &month);
    sscanf(tru_year, "%d", &year);
    int fl = 0;
    for (int i = 0; i < text->count_sentence; i++) {
        for (int j = 0; j < text->sentence[i].count_dates; j++) {
            if (text->sentence[i].dates[j][1] == month && text->sentence[i].dates[j][2] == year) {
                fl++;
                break;
            }
        }
        if (fl == 0) {
            text->sentence[i].print = 0;
        }
        fl = 0;
    }
}