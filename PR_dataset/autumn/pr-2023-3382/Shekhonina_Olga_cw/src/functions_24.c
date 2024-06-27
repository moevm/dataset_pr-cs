#include "functions_24.h"

const int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int comp(const void* a, const void* b) {
    const Date* left = *(const Date**)a;
    const Date* right = *(const Date**)b;

    if(left->total_time < right->total_time) {
        return -1;
    }
    else if(left->total_time == right->total_time) {
        return 0;
    }
    else {
        return 1;
    }
}


int is_number(wchar_t* num, int len) {
    for(int i = 0; i < len; i++) {
        if(num[i] - L'0' > 9 || num[i] - L'0' < 0) {
            return 0;
        }
    }
    return 1;
}

int wchar_to_int(wchar_t* num, int len) {
    int result = 0;
    for(int i = 0; i < len; i++) {
        result *= 10;
        result += num[i] - L'0';
    }
    return result;
}

void ExpandDates(DateArray* dates) {
    dates->capacity += STEP;
    Date** new_arr = (Date**)realloc(dates->arr, dates->capacity*sizeof(Date*));
    if(new_arr == NULL) {
        wprintf(L"Error: ошибка распределения памяти");
        free(dates->arr);
    } else {
        dates->arr = new_arr;
    }
}

int validate(wchar_t* day, wchar_t* month, wchar_t* year) {
    if(!is_number(day,2) || !is_number(month, 2) || !is_number(year, 4)) {
        return 0;
    }
    int int_day = wchar_to_int(day, 2);
    int int_month = wchar_to_int(month, 2);
    int int_year = wchar_to_int(year, 4);
    if(int_year % 4 == 0 && int_year % 100 != 0 || int_year % 400 == 0) {
        if(int_month == 2 && int_day == 29) {
            return 1;
        }
        if(int_day > 0 && int_month <= 12 && int_month > 0 && int_day <= months[int_month]) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if(int_day > 0 && int_month <= 12 && int_month > 0 && int_day <= months[int_month]) {
            return 1;
        } else {
            return 0;
        }
    }
}

const wchar_t* short_months[12] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};

void find_dates(Text* text) {
    for(int sent = 0; sent < text->count_sent; sent++) {
        for(int i = 0; i < text->pr_sent[sent]->len_sent - 10; i++) {
            if(text->pr_sent[sent]->sentence[i + 2] == L'/' && text->pr_sent[sent]->sentence[i + 5] == L'/' && (text->pr_sent[sent]->sentence[i + 10] == L' ' || text->pr_sent[sent]->sentence[i + 10] == L'.'))  {
                wchar_t* day = (wchar_t*)malloc(3 * sizeof(wchar_t));
                wcsncpy(day, text->pr_sent[sent]->sentence + i, 2);
                day[2] = L'\0';
                wchar_t* month = (wchar_t*)malloc(3 * sizeof(wchar_t));
                wcsncpy(month, text->pr_sent[sent]->sentence + i + 3, 2);
                month[2] =  L'\0';
                wchar_t* year = (wchar_t*)malloc(5 * sizeof(wchar_t));
                wcsncpy(year, text->pr_sent[sent]->sentence + i + 6, 4);
                year[4] = L'\0';
                if(validate(day, month, year)) {
                    if(text->slash_dates->size == text->slash_dates->capacity - 1) {
                        ExpandDates(text->slash_dates);
                    }
                    Date* new_date = (Date*)malloc(sizeof(Date));
                    new_date->day = day;
                    new_date->month = month;
                    new_date->year = year;
                    text->slash_dates->size++;
                    new_date->total_time = 31 * wchar_to_int(month, 2) + 365 * wchar_to_int(year, 4) + wchar_to_int(day, 2);
                    text->slash_dates->arr[text->slash_dates->size - 1] = new_date;
                }
                else {
                    free(month);
                    free(day);
                    free(year);
                }
            }
            else if(text->pr_sent[sent]->sentence[i + 4] == L'-' && text->pr_sent[sent]->sentence[i + 7] == L'-' && (text->pr_sent[sent]->sentence[i + 10] == L' ' || text->pr_sent[sent]->sentence[i + 10] == L'.'))  {
                wchar_t* day = (wchar_t*)malloc(3 * sizeof(wchar_t));
                wcsncpy(day, text->pr_sent[sent]->sentence + i + 8, 2);
                day[2] = L'\0';
                wchar_t* month = (wchar_t*)malloc(3 * sizeof(wchar_t));
                wcsncpy(month, text->pr_sent[sent]->sentence + i + 5, 2);
                month[2] =  L'\0';
                wchar_t* year = (wchar_t*)malloc(5 * sizeof(wchar_t));
                wcsncpy(year, text->pr_sent[sent]->sentence + i, 4);
                year[4] = L'\0';
                if(validate(day, month, year)) {
                    if(text->dash_dates->size == text->dash_dates->capacity - 1) {
                        ExpandDates(text->dash_dates);
                    }
                    Date* new_date = (Date*)malloc(sizeof(Date));
                    new_date->day = day;
                    new_date->month = month;
                    new_date->year = year;
                    text->dash_dates->size++;
                    new_date->total_time = 31 * wchar_to_int(month, 2) + 365 * wchar_to_int(year, 4) + wchar_to_int(day, 2);
                    text->dash_dates->arr[text->dash_dates->size - 1] = new_date;
                }
                else {
                    free(month);
                    free(day);
                    free(year);
                }
            }
            if(text->pr_sent[sent]->sentence[i + 2] == ' ' && text->pr_sent[sent]->sentence[i + 6] == ' ' &&(text->pr_sent[sent]->sentence[i + 11] == L' ' || text->pr_sent[sent]->sentence[i + 11] == L'.')) {
                for(int j = 0; j < 12; j++) {
                    if(!wcsncmp(text->pr_sent[sent]->sentence + i + 3, short_months[j], 3)) {
                        wchar_t* day = (wchar_t*)malloc(3 * sizeof(wchar_t));
                        wcsncpy(day, text->pr_sent[sent]->sentence + i, 2);
                        day[2] = L'\0';
                        wchar_t* year = (wchar_t*)malloc(5 * sizeof(wchar_t));
                        wcsncpy(year, text->pr_sent[sent]->sentence + i + 7, 4);
                        year[4] = L'\0';
                        if(validate(day, L"01", year)) {
                            if(text->space_dates->size == text->space_dates->capacity - 1) {
                                ExpandDates(text->space_dates);
                            }
                            Date* new_date = (Date*)malloc(sizeof(Date));
                            wchar_t* month = (wchar_t*)malloc(3*sizeof(wchar_t));
                            month[0] = (j / 10) + L'0';
                            month[1] = (j % 10) + 1 + L'0';
                            month[2] = L'\0';
                            new_date->day = day;
                            new_date->month = month;
                            new_date->year = year;
                            text->space_dates->size++;
                            new_date->total_time = 31 * (j + 1) + 365 * wchar_to_int(year, 4) + wchar_to_int(day, 2);
                            text->space_dates->arr[text->space_dates->size - 1] = new_date;
                        } else {
                            free(day);
                            free(year);
                        }
                    }
                }
            }
        }
    }
}

void sort_dates(Text* text) {
    qsort(text->slash_dates->arr, text->slash_dates->size, sizeof(text->slash_dates->arr), comp);
    qsort(text->dash_dates->arr, text->dash_dates->size, sizeof(text->dash_dates->arr), comp);
}

void output_sorted_dates(Text* text) {
    int i = 0;
    int j = 0;
    while(i < text->slash_dates->size || j < text->dash_dates->size) {
        if(i < text->slash_dates->size && j < text->dash_dates->size) {
            if(text->slash_dates->arr[i]->total_time < text->dash_dates->arr[j]->total_time) {
                wprintf(L"%ls/%ls/%ls\n", text->slash_dates->arr[i]->day, text->slash_dates->arr[i]->month, text->slash_dates->arr[i]->year);
                i++;
            }
            else {
                wprintf(L"%ls-%ls-%ls\n", text->dash_dates->arr[j]->year, text->dash_dates->arr[j]->month, text->dash_dates->arr[j]->day);
                j++;
            }
        }
        else if(i < text->slash_dates->size) {
            wprintf(L"%ls/%ls/%ls\n", text->slash_dates->arr[i]->day, text->slash_dates->arr[i]->month, text->slash_dates->arr[i]->year);
            i++;
        }
        else if(j < text->dash_dates->size) {
            wprintf(L"%ls-%ls-%ls\n", text->dash_dates->arr[j]->year, text->dash_dates->arr[j]->month, text->dash_dates->arr[j]->day);
            j++;
        }
    }
}


int did_date_happen(Date* date) {
    time_t now;
    struct tm *current_time;
    time(&now);
    current_time = localtime(&now);
    if (current_time->tm_mday + (current_time->tm_mon + 1) * 31 + (1900 + current_time->tm_year) * 365 > date->total_time) {
        return 1;
    } else {
        return 0;
    }
}

void did_dates_happen(Text* text) {
    for(int i = 0; i < text->space_dates->size; i++) {
        if(did_date_happen(text->space_dates->arr[i])) {
            wprintf(L"%ls.%ls.%ls", text->space_dates->arr[i]->day, text->space_dates->arr[i]->month, text->space_dates->arr[i]->year);
            wprintf(L" Happened\n");
        }
        else {
            wprintf(L"%ls.%ls.%ls", text->space_dates->arr[i]->day, text->space_dates->arr[i]->month, text->space_dates->arr[i]->year);
            wprintf(L" Not Happened\n");
        }
    }
}
