#pragma once
#include "text.h"

Word *get_name_digit(wchar_t ch);
void replace_digit(Word *word);
void replace_digit_in_sentence(Sentence *str);
void replace_digit_in_text(Text *txt);