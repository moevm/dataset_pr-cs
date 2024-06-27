#ifndef SENTFUNCS_H
#define SENTFUNCS_H

#include"structures.h"
#include<wchar.h>
#include<wctype.h>


struct Sentence sentToLower(struct Sentence snt);
void sentenceCopy(struct Sentence* dest, struct Sentence* src);
int charComparator(const void* firstSym, const void* secondSym);
wchar_t* getSentenceMask(struct Sentence snt);
int isAnagramm(struct Sentence firstSnt, struct Sentence secondSnt);
int upperSentComparator(const void* firstSnt, const void* secondSnt);
int isVowel(wchar_t letter);
void getNextLetters(wchar_t vowel, struct Sentence* snt);
wchar_t* wordToLower(wchar_t* word);
int isSeparator(wchar_t sym);
void getFirstTwoWords(struct Text* txt, wchar_t** key, wchar_t** word);
int getLen(struct Sentence snt);

#endif
