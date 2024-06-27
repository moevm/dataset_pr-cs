#pragma once
#include "structures.h"
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <stdio.h>
#include "firstProc.h"
#include "maskOfSent.h"
#include "capitalStart.h"
#include "vowelSort.h"
#include "repeatWords.h"
#include "output.h"
#include "certainWords.h"


#ifndef TEXTSIZE
#define TEXTSIZE 10
#endif

#ifndef SENTENCESIZE
#define SENTENCESIZE 100
#endif

void input(Text* text);
int firstInputOutput(Text* text);
wchar_t deleteSpaces(wchar_t bufSymbol, int* flagN);
void insertSymbol(Text* text, wchar_t symbol, int* flagN);
Sentence* firstInp();
