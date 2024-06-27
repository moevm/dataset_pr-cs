#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_text.h"
#include "sort_by_latin_letters.h"

int count_latin_letters(const char *sentence)
{
    int count = 0;

    for (int i = 0; i < strlen(sentence); i++)
    {
        if (isalpha(sentence[i]))
        {
            count++;
        }
    }
    return count;
}

int qsort_sentences(const void *a, const void *b)
{
    int countA = count_latin_letters(((Sentence *)a)->sentence);
    int countB = count_latin_letters(((Sentence *)b)->sentence);

    return countB - countA;
}

void sort_by_latin_letters(Text text)
{
    qsort(text.sentences, text.sentence_count, sizeof(Sentence), qsort_sentences);

    for (int i = 0; i < text.sentence_count; i++)
    {
        printf("%s\n", text.sentences[i].sentence);
    }
}