#include "sort_sentences.h"
#include <stdlib.h>

int compare_length_sentences(const void *a, const void *b)
{
    const Sentence *sent1 = *(Sentence**)a;
    Sentence *sent2 = *(Sentence**)b;
    return sent1->count_words - sent2->count_words;
}

void sort_sentences(Text *txt)
{
    qsort(txt->array_sentence, txt->length, sizeof(Sentence *), compare_length_sentences);
}