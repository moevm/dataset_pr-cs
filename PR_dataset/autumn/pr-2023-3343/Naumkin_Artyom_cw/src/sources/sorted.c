#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structures.h"
#include "sorted.h"


size_t count_word_len_three(const char *sentence, size_t len)
{
    size_t count = 0, word_len;
    const char* splitters = " ,";
    for (size_t i = 0; i < len; i++)
    {
        word_len = 0;
        while (i < len && !strchr(splitters, sentence[i]))
        {
            word_len++;
            i++;
        }
        if (word_len == 3)
            count++;
    }

    return count;
}


int compare_three_letter_word(const void* a, const void* b)
{
    Sentence* sentence_a = (Sentence*)a;
    Sentence* sentence_b = (Sentence*)b;
    size_t count_a = count_word_len_three(sentence_a->chars, sentence_a->size);
    size_t count_b = count_word_len_three(sentence_b->chars, sentence_b->size);

    return count_b - count_a;
}


void sort_three_letter_word(Text* text)
{
    qsort(text->sentence, text->size, sizeof(Sentence), compare_three_letter_word);
}
