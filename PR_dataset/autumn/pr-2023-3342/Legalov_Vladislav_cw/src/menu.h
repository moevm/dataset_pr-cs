#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "defines.h"
#include "structures.h"
#include "breaks_in_sentence.h"
#include "wchar_checks.h"
#include "text_base_funct.h"
#include "input_output_text.h"
#include "anagram_funct.h"
#include "replace_vowels.h"
#include "replace_words.h"

void menu(int task);
void replace_to_big_word(Text *text, wchar_t *word);
void replace_word_in_sentense(Sentence* sentence, wchar_t * word);
