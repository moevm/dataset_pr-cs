#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <string.h>
#include <ctype.h>

#include "input.h"
#include "output.h"
#include "memory.h"

#define WORD_SPLITTERS " ,."

int strCaseCmp(const char *s1, const char *s2);
int countWordInSentence(Word word, Sentence sentence);
int compare(const void *a, const void *b);
void replaceSymbolWithSubstring(Sentence *sentence, char symbol, char *substring);
void initialMandarotyProcessing();
void outputOnlyDigitsSentences();
void sortSentencesByTheNumberOfUppercaseLettersInIt();
void deleteSentenceWithTheInputtedWord();
void replaceDigitsInSentences();
void repeatSentences();

#endif
