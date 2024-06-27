#include <time.h>
#include <wchar.h>
#include <stdlib.h>
#include "struct_define.h"


struct Result find_date_in_sentance(struct Sentence* sentence){
    struct Date *dates = (struct Date*)malloc(1 * sizeof(struct Date));
    int idx = 0;
    wchar_t *word;
    word = (wchar_t *) malloc(11 * sizeof(wchar_t));
    struct Date date;
    for(int i = 0;i < sentence->len - 2; i++){
            if(sentence->str[i] == L'/' && sentence->str[i + 3]==L'/'){
                for(int k = i - 2, c = 0; k < i + 8; k++, c++){
                    word[c] = sentence->str[k];
                }
            
            swscanf(word,L"%2d/%2d/%4d", &date.day, &date.month, &date.year);
            if(date.day<32 && date.month<13 && date.year<10000){
                dates[idx] = date;
                idx++;
                }
            struct Date *tmp;
            tmp = (struct Date*)realloc(dates, (idx + 1) * sizeof(struct Date));
            dates = tmp;
            }
            else if(sentence->str[i] == L'-' && sentence->str[i + 3]==L'-'){
                for(int k = i - 4, c = 0; k < i + 6; k++, c++){
                    word[c] = sentence->str[k];
                }
                swscanf(word,L"%4d-%2d-%2d", &date.year, &date.month, &date.day);
                if(date.day<32 && date.month<13 && date.year<10000){
                    dates[idx] = date;
                    idx++;
                }
                struct Date *tmp;
                tmp = (struct Date*)realloc(dates, (idx + 1) * sizeof(struct Date));
                dates = tmp;
            }
    }
    struct Result res;
    res.dates = dates;
    res.len = idx;
    return res;
}

int date_sort(struct Date a, struct Date b){
    if ( a.year > b.year ) {
        return 1;
    }
    if(a.year < b.year){
        return 0;
    }
    if(a.month > b.month){
        return 1;
    }
    if(a.month < b.month){
        return 0;
    }
    if(a.day > b.day){
        return 1;
    }
    if(a.day < b.day){
        return 0;
    }
    return 0;
}

void print_sorted_dates(struct Text text1){
    int idx = 0;
    struct Date *dates = (struct Date*)malloc((idx + 1) * sizeof(struct Date));
    for (int i = 0; i < text1.len; i++){
        struct Result res = find_date_in_sentance(text1.text[i]);
        struct Date *dates_in_sentance = res.dates;
        int len = res.len;
        for (int j = 0; j < len; j++){
            dates[idx] = dates_in_sentance[j];
            idx++;
            struct Date *tmp;
            tmp = (struct Date*)realloc(dates, (idx + 1) * sizeof(struct Date));
            dates = tmp;
        }
    }
    for(int i = 0; i < idx - 1; i++) {
        for(int j = 0; j < idx - i - 1 ; j++) {
            if(date_sort(dates[j],dates[j+1])) {
                struct Date tmp = dates[j];
                dates[j] = dates[j+1] ;
                dates[j+1] = tmp;
            }
        }
    }
    for(int i = 0;i < idx; i++){
        wprintf(L"%02d.%02d.%04d\n", dates[i].day, dates[i].month, dates[i].year);
    }
}

struct Date now_day(){
    struct Date d;
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);
    d.year = aTm->tm_year+1900;
    d.month = aTm->tm_mon+1;
    d.day = aTm->tm_mday;
    return d;
}

void happened_dates(struct Text txt){
    wchar_t months[][13] = {
            L"Jan",L"Feb",L"Mar",L"Apr",L"May",L"Jun",L"Jul",L"Aug",L"Sep",L"Oct",L"Nov",L"Dec"
    };
    struct Date date;
    for(int i = 0; i < txt.len;i++){
        for(int j = 0;j < txt.text[i]->len - 11; j++){
            wchar_t *word = (wchar_t *) malloc(11 * sizeof(wchar_t));
            if (j == 12){
                int asd = 0;
            }
            wchar_t *day;
            int iday = 0;
            wchar_t *month;
            month = (wchar_t *)malloc(4 * sizeof(wchar_t));
            int imonth = 0;
            wchar_t *year;
            year = (wchar_t *)malloc(5 * sizeof(wchar_t));
            int iyear = 0;
            for (int k = j, c = 0; c < 11; k++, c++){
                word[c] = txt.text[i]->str[k];
            }
            if (word[2] != ' ' || word[6] != ' '){
                continue;
            }
            swscanf(word, L"%d", &iday);
                if (iday > 32 || iday == 0){
                    continue;
                }
            for (int m = 3; m < 6; m++){month[m - 3] = word[m];}
            month[3] = '\0';
            for (int r = 0; r < 12; r++){
                if (!wcscasecmp(month, months[r])){
                        imonth = r + 1;
                        break;
                    }
                }
            if (imonth == 0){
                continue;
            }
            for (int m = 7; m < 11; m++){year[m - 7] = word[m];}
            swscanf(year, L"%d", &iyear);
            date.day = iday;
            date.month = imonth;
            date.year = iyear;
            if(date_sort(now_day(), date)){
                wprintf(L"%02d.%02d.%04d Happened\n", date.day, date.month, date.year);
            }else{
                wprintf(L"%02d.%02d.%04d Not Happened\n", date.day, date.month, date.year);
            }
            free(word);
            free(year);
            free(month);
        }
    }
}
