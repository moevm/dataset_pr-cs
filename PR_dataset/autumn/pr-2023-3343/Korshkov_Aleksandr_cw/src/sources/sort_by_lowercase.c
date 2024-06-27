#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../include/sort_by_lowercase.h"

int countLowerCase(char *sentence) // считает кол-во строчных букв
{
    int count = 0;
    for (int i = 0; i < strlen(sentence); i++)
    {
        if (islower(sentence[i]) && isalpha(sentence[i]))
            count++;
    }
    return count;
}

int compare(const void *sentence1, const void *sentence2) // функция-компоратор
{
    char* sentence_1 = *((char**)sentence1);
    char* sentence_2 = *((char**)sentence2);
    int count1 = countLowerCase(sentence_1), count2 = countLowerCase(sentence_2);
    
    if (count1 > count2) return -1;
    if (count1 < count2) return 1;
    else return 0;
}

void sortSentences(char **sentences, int *count) //сортирует предложения по убыванию
{
    qsort(sentences, *count, sizeof(char *), compare);
}