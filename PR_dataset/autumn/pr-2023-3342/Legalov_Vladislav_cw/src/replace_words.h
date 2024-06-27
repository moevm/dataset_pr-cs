#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "structures.h"
#include "breaks_in_sentence.h"
#include "wchar_checks.h"


int replace_words_in_text(Text *text);
void replace_words_in_sentence(Sentence* sentence, wchar_t *first, wchar_t *second);
BreaksData* find_strs(Sentence* sentence, wchar_t *first, int size_breaks);
int get_words(Text *text, wchar_t **first, wchar_t **second);

