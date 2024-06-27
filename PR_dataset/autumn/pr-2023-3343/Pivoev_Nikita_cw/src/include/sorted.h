#ifndef SORTED_H
#define SORTED_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "struct.h"
#include "splittedSentence.h"
#include "free.h"

int compareVowels(const void* a, const void* b);
void sortWords(Text text);

#endif