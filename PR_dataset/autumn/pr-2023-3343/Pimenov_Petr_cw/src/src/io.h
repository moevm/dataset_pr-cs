#ifndef IO_H
#define IO_H

#include "data.h"

void writeString(wchar_t *string);

void writeSentence(Sentence sentence);

void writeText(Text text);

void writeError(wchar_t *cause);

void writeWordCounts(WordCount *counts, size_t countsSize);

int readInt();

wchar_t *readString();

Sentence readSentence();

Text readText();

#endif
