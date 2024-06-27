#ifndef UTIL_H
#define UTIL_H

#include <wchar.h>

wchar_t *getWordDelimiters();

int compareWordCountsQsort();

int compareWordCountsBsearch();

int isLatin(wchar_t chr);

size_t countLatin(Sentence sentence);

int compareSortByLatinQsort(const void *a, const void *b);

int hasUppercaseLetters(Sentence sentence);

#endif
