#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <wctype.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#include "structs.h"
#include "find_dates.h"
#include "is_date_correct.h"
#include "memory_error.h"


void find_dates (struct Text text)
{
    setlocale(LC_ALL, "");

    int is_memory_ok = 1;

    for (size_t i = 0; i < text.count && is_memory_ok; i++)
    {   
        int len = wcslen(text.text[i].sentence);

        if (len > 3 && text.text[i].sentence[len - 3] == L'г' && text.text[i].sentence[len - 4] == L' ') // Поиск начинается, если предложение оканчивается на г.
        {
            int *spaces_pos = (int *)malloc(sizeof(int));
            if (spaces_pos == NULL) memory_error(is_memory_ok, L"find_dates.c spaces_pos");

            int count_of_spaces = 0;

            for (size_t j = 0; j < len; j++) // Нахождение позиций пробелов
            {
                if (text.text[i].sentence[j] == L' ')
                {
                    spaces_pos[count_of_spaces++] = j;
                    spaces_pos = (int *)realloc(spaces_pos, sizeof(int) * (count_of_spaces + 1));
                    if (spaces_pos == NULL) memory_error(is_memory_ok, L"find_dates.c spaces_pos");
                }
            }

            if (count_of_spaces >= 3)
            {
                struct tm m_time = {0};

                const wchar_t *months[] = {L"января", L"февраля", L"марта", L"апреля", L"мая", L"июня",
                                            L"июля", L"августа", L"сентября", L"октября", L"ноября", L"декабря", 
                                            L"january", L"february", L"march", L"april", L"may", L"june",
                                            L"july", L"august", L"september", L"october", L"november", L"december"};

                int day = 0, year = 0;
                int pos = count_of_spaces > 3 ? spaces_pos[count_of_spaces - 4] + 1 : 0; // Нахождение позиции, с которой начинается дата
                int is_correct_month_len = 0, is_correct_symb_len = 0, is_correct_year_len = 0;

                wchar_t month[30], new_date[30], end_symb[30];
                
                if (spaces_pos[count_of_spaces - 2] - spaces_pos[count_of_spaces - 3] < 20) is_correct_month_len = 1;

                if (spaces_pos[count_of_spaces - 1] - spaces_pos[count_of_spaces - 2] < 20) is_correct_year_len = 1;

                if (len - spaces_pos[count_of_spaces - 1] < 20) is_correct_symb_len = 1;


                if (is_correct_month_len && is_correct_symb_len && is_correct_year_len)
                {
                    if (swscanf(text.text[i].sentence + pos, L"%d %ls %d %ls", &day, &month, &year, &end_symb) == 4 && wcscmp(end_symb, L"г.") == 0)
                    {
                        m_time.tm_mon = -1;
                        for (size_t k = 0; k < 24; k++) // Замена месяца на его число
                        {
                            if (wcsncasecmp(month, months[k], 1) == 0) m_time.tm_mon = k % 12;
                        }

                        m_time.tm_mday = day;

                        m_time.tm_year = year;
                        m_time.tm_year -= 1900;

                        if (is_date_correct(day, m_time.tm_mon, year)) // Замена формата даты в случае её корректности
                        {
                            wcsftime(new_date, 30, L"%d/%m/%Y.\n", &m_time);
                            wcscpy(text.text[i].sentence + pos, new_date);
                        }
                    }
                }
            }

            if (is_memory_ok) free(spaces_pos);
        }
    }
}