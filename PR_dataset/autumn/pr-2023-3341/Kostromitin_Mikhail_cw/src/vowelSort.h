#pragma once
#include "structures.h"
#include "countWords.h"
#include <wctype.h>
#include <string.h>
#include <stdlib.h>
#include "fillArr.h"


void sortByNumOfVowel(Text* text);
int vowelcmp(const void* a, const void* b);
