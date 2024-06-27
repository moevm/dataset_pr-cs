#ifndef MEMORY_H
#define MEMORY_H

#include "data.h"

void freeSentence(Sentence sentence);

void freeSentences(Sentence *sentences, size_t size);

void freeText(Text text);

void freeWordCounts(WordCount *counts, size_t size);

#endif
