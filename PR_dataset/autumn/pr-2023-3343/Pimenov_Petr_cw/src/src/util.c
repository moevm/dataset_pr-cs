#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "config.h"
#include "data.h"

wchar_t *getWordDelimiters()
{
    size_t length = wcslen(SENTENCE_ENDS) + wcslen(TEXT_END) + wcslen(SPACES) + wcslen(WORD_DELIMITERS);
    wchar_t *delimiters = (wchar_t *)calloc(sizeof(wchar_t), length + 1);
    wcscat(delimiters, SENTENCE_ENDS);
    wcscat(delimiters, TEXT_END);
    wcscat(delimiters, SPACES);
    wcscat(delimiters, WORD_DELIMITERS);
    return delimiters;
}

int compareWordCountsQsort(const void *a, const void *b)
{
    const WordCount wca = *((const WordCount *)a);
    const WordCount wcb = *((const WordCount *)b);
    return wcscmp(wca.data, wcb.data);
}

int compareWordCountsBsearch(const void *a, const void *b)
{
    const wchar_t *wca = (const wchar_t *)a;
    const WordCount wcb = *((const WordCount *)b);
    return wcscmp(a, wcb.data);
}

int isLatin(wchar_t chr)
{
    return (65 <= chr && chr <= 90) || (97 <= chr && chr <= 122);
}

size_t countLatin(Sentence sentence)
{
    size_t counter = 0;
    for (size_t i = 0; i < sentence.length; ++i)
    {
        if (isLatin(sentence.data[i]))
        {
            counter++;
        }
    }
    return counter;
}

int compareSortByLatinQsort(const void *a, const void *b)
{
    const Sentence sa = *((const Sentence *)a);
    const Sentence sb = *((const Sentence *)b);
    return countLatin(sa) - countLatin(sb);
}

int hasUppercaseLetters(Sentence sentence)
{
    for (size_t i = 0; i < sentence.length; ++i)
    {
        if (iswupper(sentence.data[i]))
        {
            return 1;
        }
    }
    return 0;
}
