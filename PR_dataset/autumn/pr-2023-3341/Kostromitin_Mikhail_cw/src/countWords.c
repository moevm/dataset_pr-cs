#include "countWords.h"


int countWords(Sentence* sentence)
{
    int words = 0;

    for (int i = 1; i < sentence->len; i++)
    {
        if (!(wcschr(L" ,.\t\n", sentence->sentence[i - 1])) && wcschr(L" ,.\t\n", sentence->sentence[i])) words++;
    }

    return words;
}
