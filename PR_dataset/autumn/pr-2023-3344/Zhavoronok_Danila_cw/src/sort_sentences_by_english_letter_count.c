#include "sort_sentences_by_english_letter_count.h"
#include <stdlib.h>

int english_letter_count_comp(sentence **a, sentence **b)
{
    // printf("%d %d\n", a->counter, b->counter);
    return (*a)->counter - (*b)->counter;
    // return (*b)->counter - (*a)->counter;
}

void sort_sentences_by_english_letter_count(text *text)
{
    qsort(text->sentences, text->length, sizeof(sentence *), (int (*)(const void *, const void *))english_letter_count_comp);
}
