#include "find_dates.h"

//Найти и вывести все даты в тексте заданные
//в виде “ DD/MM/YYYY ” или “ YYYY-MM-DD ” в порядке возрастания этих дат. 
void find_dates(text_t* words)
{
    size_t top = 0;
    size_t capacity = 10;
    date_t** dates = (date_t**)malloc(sizeof(date_t*) * 10);
    if(dates == NULL) printError(L"Failed to allocate memory for the struct date_t**");
    for(size_t i = 0; i < 10; ++i){
        dates[i] = (date_t*)malloc(sizeof(date_t));
        dates[i]->date = (char*)malloc(sizeof(char) * 10);
        if(dates[i] == NULL) printError(L"Failed to allocate memory for the struct date_t*");
        if(dates[top]->date == NULL) printError(L"Failed to allocate memory for the date");
    }
    char* curline = (char*)malloc(sizeof(char) * 10);
    if(curline == NULL) printError(L"Failed to allocate memory for the curline [fn: find_dates]");
    for(size_t _ = 0; _ < words->size; ++_){
        wchar_t* curline_wc = words->data[_]->data;
        size_t check_len = wcstombs(curline, curline_wc, 10);
        if(check_len > 0){
            curline[check_len] = '\0';
        } else {
            printError(L"Failed to convert wchar_t* to char*");
        }
        const char* format1 = "%d/%m/%Y";
        const char* format2 = "%F";
        struct tm* time_info = (struct tm*)malloc(sizeof(struct tm));
        if(time_info == NULL) printError(L"Failed to allocate memory for the struct tm*"); 
        if(strptime(curline, format1, time_info) != NULL || strptime(curline, format2, time_info) != NULL){
            strncpy(dates[top]->date, curline, 11);
            dates[top]->time = mktime(time_info);
            top++;
            if(top >= capacity){
                capacity += 10;
                dates = (date_t**)realloc(dates, sizeof(date_t*) * capacity);
                if(dates == NULL) printError(L"Failed to reallocate memory for the struct date_t**");
                for(size_t i = (capacity - 10); i < (capacity); ++i){
                    dates[i] = (date_t*)malloc(sizeof(date_t));
                    dates[i]->date = (char*)malloc(sizeof(char) * 10);
                    if(dates[i] == NULL) printError(L"Failed to allocate memory for the struct date_t*");
                    if(dates[i]->date == NULL) printError(L"Failed to allocate memory for the date");
                }
            }
        }
    free(time_info);
    }
    free(curline);
    qsort(dates, top, sizeof(date_t*), compare);
    for(int i = 0; i < top; ++i){
        wprintf(L"%ld: %s\n", i, dates[i]->date);
        free(dates[i]->date);
        free(dates[i]);
    }
    free(dates);
}
