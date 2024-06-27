#ifndef INPUT_H
#define INPUT_H

#include "structures.h"

int getCommand();
wchar_t* getFirstWord();
wchar_t *getPattern();
Sentence inputSentence(int *sentenceCounter);
Text inputText();
float calculateAverageWordsLength(wchar_t *sentence);
wchar_t **getPunctuation(Sentence sentence);

#endif