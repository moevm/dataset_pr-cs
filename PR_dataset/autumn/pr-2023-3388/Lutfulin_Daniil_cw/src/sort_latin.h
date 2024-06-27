#pragma once
#include "structs.h"
#include <stdlib.h>

#define LATIN_CHARS L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"

size_t check_latin(const Sentence*);
int compare_latin(const void*, const void*);
void sort_latin(Text*);