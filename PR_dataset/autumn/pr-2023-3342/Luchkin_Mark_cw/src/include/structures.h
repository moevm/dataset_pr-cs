#ifndef STRUCTERS_H
#define STRUCTERS_H

#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

typedef struct{
    wchar_t* chars;
    int size;
    float averageWordsLength;
    int wordCounter;
    wchar_t** punctuation;
}Sentence;

typedef struct{
    Sentence* sentences;
    int size;
}Text;

#endif