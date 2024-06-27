#ifndef STRUCTERES_H
#define STRUCTERES_H

#include <wchar.h>

typedef struct {
    wchar_t* line;
    int sentenceSize;
} Sentence;

typedef struct {
    Sentence* sentences;
    int sentencesNumber;
} Text;

Text* createText();

#endif