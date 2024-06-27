#pragma once
#include "library.h"
struct Sentence *readSentence();
struct Text readText();
void format (struct Text *t);
int Repeating(wchar_t* sent1,wchar_t* sent2);
