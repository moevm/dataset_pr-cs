#ifndef TIMEPROCESSING_H
#define TIMEPROCESSING_H

#include "structures.h"
void* getTime(const wchar_t *sentence, unsigned int index);
void processTime(int *sentenceTime, unsigned int index);
void findTimeInSentences(Text *text);

#endif