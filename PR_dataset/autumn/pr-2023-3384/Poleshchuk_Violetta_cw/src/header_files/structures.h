#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <wchar.h>

typedef struct{
    int len;
    wchar_t* symbols;
    wchar_t* punctuation;
}Word;

typedef struct {
    wchar_t *content;
    int len;
    Word* words;
    int counterWords;
} Sentence;

typedef struct{
    Sentence *sentences;
    int countSentences;
    int countWords;
    int countSymbols;
} Text;


#endif 