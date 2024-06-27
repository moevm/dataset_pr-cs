#include "time_funcs.h"
void check_time(struct Text text)
{
    struct Date *dates = (struct Date *)malloc(STEP * sizeof(struct Date));
    int size = STEP;
    int i = 0, errflag = 0;
    struct Date d1;
    for (int g = 0; g < text.length; g++)
    {
        struct Sentence *str = text.text[g];
        if (str->str_length >= 10)
        {
            for (int j = 0; j < str->str_length - 9; j++)
            {
                if (iswdigit(str->sentence[j]) && iswdigit(str->sentence[j + 1]) && str->sentence[j + 2] == L'/' && iswdigit(str->sentence[j + 3]) && iswdigit(str->sentence[j + 4]) && str->sentence[j + 5] == L'/' && iswdigit(str->sentence[j + 6]) && iswdigit(str->sentence[j + 7]) && iswdigit(str->sentence[j + 8]) && iswdigit(str->sentence[j + 9]))
                {
                    wchar_t *maybe_date = wcsdup(str->sentence + j);
                    swscanf(maybe_date, L"%2d/%2d/%4d", &d1.day, &d1.month, &d1.year);
                    if (error_data_check(d1))
                    {
                        dates[i] = d1;
                        i++;
                    }
                    else
                        errflag = 1;
                    free(maybe_date);
                }
                if (iswdigit(str->sentence[j]) && iswdigit(str->sentence[j + 1]) && str->sentence[j + 2] == L'-' && iswdigit(str->sentence[j + 3]) && iswdigit(str->sentence[j + 4]) && str->sentence[j + 5] == L'-' && iswdigit(str->sentence[j + 6]) && iswdigit(str->sentence[j + 7]) && iswdigit(str->sentence[j + 8]) && iswdigit(str->sentence[j + 9]))
                {
                    wchar_t *maybe_date = wcsdup(str->sentence + j);
                    swscanf(maybe_date, L"%2d-%2d-%4d", &d1.day, &d1.month, &d1.year);
                    if (error_data_check(d1))
                    {
                        dates[i] = d1;
                        i++;
                    }
                    else
                        errflag = 1;
                    free(maybe_date);
                }
                if (i == size - 2)
                {
                    size += STEP;
                    dates = (struct Date *)realloc(dates, sizeof(struct Date) * size);
                }
            }
        }
    }
    qsort(dates, i, sizeof(struct Date), cmp);
    if (errflag == 0)
    {
        for (int j = 0; j < i; j++)
        {
            wprintf(L"%02d.%02d.%04d\n", dates[j].day, dates[j].month, dates[j].year);
        }
    }
    else
    {
        wprintf(L"Error: Выполнение функции прервано, так как в тексте встречена невозможная дата\n");
    }
    free(dates);
}
int cmp(const void *aa, const void *bb)
{
    struct Date *a = (struct Date *)aa;
    struct Date *b = (struct Date *)bb;
    if (a->year > b->year)
    {
        return 1;
    }
    else if (a->year == b->year && a->month > b->month)
    {
        return 1;
    }
    else if (a->year == b->year && a->month == b->month && a->day > b->day)
    {
        return 1;
    }
    else if (a->year == b->year && a->month == b->month && a->day == b->day)
    {
        return 0;
    }
    return -1;
}

int error_data_check(struct Date date)
{
    int month = date.month;
    if (date.year > 9999)
        return 0;
    if (month > 12)
        return 0;
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && date.day > 31)
        return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && date.day > 30)
        return 0;
    if ((month == 2 && date.year % 100 != 0 && date.year % 4 == 0 && date.day > 29) || (month == 2 && ((date.year % 100 == 0 || date.year % 4 != 0) && !(date.year % 400 == 0)) && date.day > 28) || (date.year % 400 == 0 && date.day > 29))
        return 0;
    return 1;
}

void get_and_check_dates(struct Text txt)
{
    time_t now;
    time(&now);
    struct tm *time;
    struct tm *nowadays = localtime(&now);
    nowadays->tm_mon++;
    nowadays->tm_year += 1900;
    int j = 0, maxlen = STEP;
    for (int i = 0; i < txt.length; i++)
    {
        wchar_t *token, *day, *month, *ptr;
        token = wcstok(txt.text[i]->sentence, L" ,.'\n'", &ptr);
        wchar_t *year = token;
        int k = 0;
        while (token != NULL)
        {
            if (k > 1)
            {
                if (wcslen(day) && wcslen(month) && wcslen(year))
                {
                    if (time = check_for_date(day, month, year))
                    {
                        if (check_if_happened(time, nowadays) == 1)
                        {
                            wprintf(L"%02d.%02d.%04d Happened\n", time->tm_mday, time->tm_mon, time->tm_year);
                        }
                        else if (check_if_happened(time, nowadays) == 0)
                        {
                            wprintf(L"%02d.%02d.%04d Not happened\n", time->tm_mday, time->tm_mon, time->tm_year);
                        }
                        else if (check_if_happened(time, nowadays) == 2)
                        {
                            wprintf(L"%02d.%02d.%04d It's today\n", time->tm_mday, time->tm_mon, time->tm_year);
                        }
                        free(time);
                    }
                }
            }
            token = wcstok(NULL, L" ,.'\n'", &ptr);
            day = month;
            month = year;
            year = token;
            k++;
        }
    }
}

struct tm *check_for_date(wchar_t *day, wchar_t *month, wchar_t *year)
{
    int flag = 0;
    wchar_t check_month[][4] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
    struct tm *time = (struct tm *)malloc(sizeof(struct tm));
    if (wcslen(day) == 2)
    {
        if (iswdigit(day[0]) && iswdigit(day[1]))
        {
            time->tm_mday = wcstol(day, NULL, 10);
            flag++;
        }
    }
    else if (wcslen(day) == 1)
    {
        if (iswdigit(day[0]))
        {
            time->tm_mday = wcstol(day, NULL, 10);
            flag++;
        }
    }
    for (int i = 0; i < 12; i++)
    {
        if (wcscmp(check_month[i], month) == 0)
        {
            time->tm_mon = i + 1;
            flag++;
        }
    }
    if (wcslen(year) == 4)
    {
        if (iswdigit(year[0]) && iswdigit(year[1]) && iswdigit(year[2]) && iswdigit(year[3]))
        {
            time->tm_year = wcstol(year, NULL, 10);
            flag++;
        }
    }
    else if (wcslen(year) == 3)
    {
        if (iswdigit(year[0]) && iswdigit(year[1]) && iswdigit(year[2]))
        {
            time->tm_year = wcstol(year, NULL, 10);
            flag++;
        }
    }
    else if (wcslen(year) == 2)
    {
        if (iswdigit(year[0]) && iswdigit(year[1]))
        {
            time->tm_year = wcstol(year, NULL, 10);
            flag++;
        }
    }
    else if (wcslen(year) == 1)
    {
        if (iswdigit(year[0]))
        {
            time->tm_year = wcstol(year, NULL, 10);
            flag++;
        }
    }
    if (flag == 3)
    {
        return time;
    }
    free(time);
    return 0;
}

int check_if_happened(struct tm *time1, struct tm *time2)
{
    if (time1->tm_year < time2->tm_year)
    {
        return 1;
    }
    else if (time1->tm_year > time2->tm_year)
    {
        return 0;
    }
    else if (time1->tm_year == time2->tm_year && time1->tm_mon < time2->tm_mon)
    {
        return 1;
    }
    else if (time1->tm_year == time2->tm_year && time1->tm_mon > time2->tm_mon)
    {
        return 0;
    }
    else if (time1->tm_year == time2->tm_year && time1->tm_mon == time2->tm_mon && time1->tm_mday < time2->tm_mday)
    {
        return 1;
    }
    else if (time1->tm_year == time2->tm_year && time1->tm_mon == time2->tm_mon && time1->tm_mday > time2->tm_mday)
    {
        return 0;
    }
    else if (time1->tm_year == time2->tm_year && time1->tm_mon == time2->tm_mon && time1->tm_mday == time2->tm_mday)
    {
        return 2;
    }
}
