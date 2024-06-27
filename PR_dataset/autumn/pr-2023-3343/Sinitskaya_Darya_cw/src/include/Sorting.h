#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>

#include"Struct.h"

int Count_Latin_Letters(wchar_t *sentence);
int Compare_Sentences(const void *a, const void *b);
void Sorting(Text *text);

#endif