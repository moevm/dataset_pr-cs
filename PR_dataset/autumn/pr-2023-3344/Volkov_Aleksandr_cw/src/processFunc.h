#pragma once
#include "structures.h"

int compareSortByAlphabet(const void *a, const void *b);
int areAnagrams(wchar_t *str1, wchar_t *str2);
void sentenceAnagrams(struct Text *text);
int compareSortUpper(const void *a, const void *b);
void sortSentencesByUpper(struct Text *text);
int replaceVowels(struct Text *text);
int replaceWordInSentence(wchar_t **sentence, int *len, int *capacity, const wchar_t *oldWord, const wchar_t *newWord);
int replaceWordInText(struct Text *text, const wchar_t *oldWord, const wchar_t *newWord);
wchar_t *readWord(int *flag);
int palindromSentence(wchar_t *str);
void palindromInText(struct Text *text);

