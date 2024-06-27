#ifndef SORT_SENTENCES_H 
#define SORT_SENTENCES_H

#include <wchar.h>
#include <stdlib.h>
#include "struct.h"

int getCode(wchar_t* sentence);
int cmp(const void* a, const void* b);
void sortBySum(Text* text);

#endif