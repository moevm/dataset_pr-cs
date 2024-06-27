#pragma once
#include "structures.h"
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include "countWords.h" 
#include "fillArr.h"


void maskOfSent(Text* text);
void freeArr(wchar_t* arr[], int size);
void maskForTwoWords(wchar_t mask[], int* maskLen, wchar_t firstWord[], wchar_t secondWord[]);
int cmp(const void* a, const void* b);
