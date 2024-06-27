#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <wchar.h>

#include "textHandle.h"
#include "struct.h"

int get_last_word_length(Sentence sentence);
int compare_sentences_by_last_word_length(const void *a, const void *b);
void sort_text_by_last_word_length(Text text);

#endif
