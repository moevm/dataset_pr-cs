#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <wchar.h>

typedef struct
{
    wchar_t *sentence;
} Sentence;

typedef struct
{
    Sentence *sentences;
    unsigned int num_sentences;
} Text;

void freeText(Text *text);
void printText(Text *text);

#endif