#include <stdio.h>
#include <ctype.h>
#include "structures.h"
#include "task_9.h"


size_t sum_word(const char* sentence, size_t len)
{
    size_t sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (isdigit(sentence[i]))
        {
            size_t digit = sentence[i] - '0';
            sum += digit;
        }
    }

    return sum;
}


int compare_sum(const void* a, const void* b)
{
    const Sentence* sentence_a = (const Sentence*)a;
    const Sentence* sentence_b = (const Sentence*)b;

    size_t count_a = sum_word(sentence_a->chars, sentence_a->size);
    size_t count_b = sum_word(sentence_b->chars, sentence_b->size);

    return count_a - count_b;
}


void sort_count_words(Text* text)
{
    qsort(text->sentence, text->size, sizeof(Sentence), compare_sum);
}
