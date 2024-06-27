#include <stdlib.h>

#include "memory.h"
#include "data.h"

void freeSentence(Sentence sentence)
{
    free(sentence.data);
}

void freeSentences(Sentence *sentences, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(sentences[i].data);
    }
}

void freeText(Text text)
{
    freeSentences(text.data, text.length);
    free(text.data);
}

void freeWordCounts(WordCount *counts, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(counts[i].data);
    }
}
