#pragma once
#include <stdlib.h>
#include "structs.h"
#include "leave.h"

#define SENT_END L'\0'
#define BIG_WORD L"(большое слово)"
#define MAX_BIG_WORD_LEN 100

size_t get_big_word_len();
Sentence *replace_big_word(Sentence*, size_t);
void replace_big_in_text(Text*, size_t);
