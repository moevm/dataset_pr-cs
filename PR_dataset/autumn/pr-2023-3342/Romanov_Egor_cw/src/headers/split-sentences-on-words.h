#ifndef SPLIT_SENTENCES_ON_WORDS_H
#define SPLIT_SENTENCES_ON_WORDS_H
#include "structs.h"
#include <wchar.h>
#include <stdlib.h>
int check_symbol_to_skip(wchar_t symbol);
void split_sentences_on_words(struct Text text);
#endif