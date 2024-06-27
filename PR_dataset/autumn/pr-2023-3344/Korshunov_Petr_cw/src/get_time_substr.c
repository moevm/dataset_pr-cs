#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"

void getTimeSubstrings(TEXT *text)
{
    time_t now;
    time(&now);
    for (int i = 0; i < text->len; i++)
    {
        wchar_t *sent = (wchar_t *)malloc(text->sents[i]->size);
        if (!sent)
        {
            wprintf(L"Error: Failed to allocate memory for the sentence.\n");
            exit(0);
        }
        wcscpy(sent, text->sents[i]->sent);
        wchar_t *pos_time = wcspbrk(sent, L":");
        while (pos_time != NULL)
        {
            if (pos_time - sent >= 2 && pos_time - sent <= wcslen(sent) - 3)
            {
                int hrs, min1, min2;
                if (swscanf(pos_time - 2, L"%2d:%1d%1d", &hrs, &min1, &min2) == 3 && hrs < 24 && min1 < 6 && min2 < 10)
                {
                    struct tm time;
                    time = *localtime(&now);
                    char *time_str = (char *)malloc(6 * sizeof(char));
                    if (!time_str)
                    {
                        wprintf(L"Error: Failed to allocate memory for the sentence.\n");
                        exit(0);
                    }
                    sprintf(time_str, "%d:%d%d", hrs, min1, min2);
                    time_str[5] = '\0';
                    if (strptime(time_str, "%H:%M", &time) != NULL)
                    {   
                        wprintf(L"%d %d\n", i + 1, abs(difftime(now, mktime(&time)) / 60));
                        free(time_str);
                    }
                }
            }
            pos_time = wcspbrk(pos_time + 1, L":");
        }
        free(sent);
    }
    return;
}