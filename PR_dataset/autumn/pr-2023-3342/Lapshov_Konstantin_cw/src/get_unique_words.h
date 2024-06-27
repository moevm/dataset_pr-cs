#pragma once
#include "structures.h"

void get_unique_words(struct Text text);
int check_similar_word(struct Unique_Word* list, size_t list_len, wchar_t *word);