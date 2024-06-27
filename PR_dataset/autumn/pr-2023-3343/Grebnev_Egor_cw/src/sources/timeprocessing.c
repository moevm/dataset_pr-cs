#include <time.h>
#include <stdlib.h>
#include <wctype.h>
#include "timeprocessing.h"
#include "memory.h"
#include "log.h"

#define TIME_FORMAT 5 // like 09:11

void *getTime(const wchar_t *sentence, unsigned int index)
{
    if (wcslen(sentence) < TIME_FORMAT)
        return 0;

    size_t sentenceLen = wcslen(sentence);

    for (unsigned int i = 0; i < sentenceLen - TIME_FORMAT; i++)

        if (iswdigit((wint_t)sentence[i]) && iswdigit((wint_t)sentence[i + 1]) &&
            sentence[i + 2] == L':' &&
            iswdigit((wint_t)sentence[i + 3]) && iswdigit((wint_t)sentence[i + 4]))
        {
            int hours = (sentence[i] - L'0') * 10 + (sentence[i + 1] - L'0');
            int mins = (sentence[i + 3] - L'0') * 10 + (sentence[i + 4] - L'0');

            if (hours >= 0 && hours <= 23 && mins >= 0 && mins <= 59)
            {
                int *time = (int *)malloc(2 * sizeof(int));
                checkMemoryAllocation(time, L"Lack of memory for time processing");
                time[0] = hours, time[1] = mins;
                return time;
            }
            else
                logWarn(L"Incorrect time format in %d sentences", index);
        }

    return NULL;
}

void processTime(int *sentenceTime, unsigned int index)
{
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int currentMinutes = localTime->tm_hour * 60 + localTime->tm_min;

    int totalMinutes = sentenceTime[0] * 60 + sentenceTime[1];
    logInfoDefault(L"Подстрока в предложении %d, минут до текущего времени: %d", index + 1, abs(totalMinutes - currentMinutes));
}
void findTimeInSentences(Text *text)
{
    for (unsigned int i = 0; i < text->num_sentences; ++i)
    {
        wchar_t *sentence = text->sentences[i].sentence;

        int *time = getTime(sentence, i);

        if (time)
        {
            processTime(time, i);
            free(time);
        }
    }
}
