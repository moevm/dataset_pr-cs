#ifndef REMOVE_SENTENCES_H 
#define REMOVE_SENTENCES_H

#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

wchar_t* getLastWord(Sentence* sentence);
int countConsonants(wchar_t* last_word);
void removeSentences(Text* text);

#endif