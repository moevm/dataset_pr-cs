#ifndef FIND_H
#define FIND_H

#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <stdlib.h>

#define CHUNK 40
#include "textHandle.h"
#include "struct.h"

int contains_word_in_sentence(Sentence *sentence, wchar_t *word);
int *find_indexes(Text text, wchar_t *word, int *cnt);
void find_word_usage(Text text);
void print_found_words(Text text, int amount_of_words, wchar_t *found_words);
int is_unique(wchar_t *word, int amount_of_words, wchar_t *found_words);
#endif
