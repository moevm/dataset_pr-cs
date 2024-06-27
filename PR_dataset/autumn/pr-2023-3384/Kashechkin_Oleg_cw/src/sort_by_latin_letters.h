#pragma once

#include "read_text.h"

int count_latin_letters(const char *sentence);
int qsort_sentences(const void *a, const void *b);
void sort_by_latin_letters(Text text);