#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/proc_time.h"

void secondsToTime(char **sentences, int *count) // считает секунды и выводить их в опредеённом формате
{
    for (int i = 0; i < *count; i++)
    {
        int seconds = 0;
        char *word = strtok(sentences[i], " .,\n\t\v\f\r");
        while (word != NULL)
        {
            if (strstr(word, "sec") != NULL)
            {
                seconds += atoi(word);
            }
            word = strtok(NULL, " .,\n\t\v\f\r");
        }
        int hours = (seconds / 3600);
        seconds -= (hours * 3600);
        int minutes = (seconds / 60);
        seconds -= (minutes * 60);
        printf("%d:%d:%d\n", hours, minutes, seconds);
        free(sentences[i]);
    }
    
}