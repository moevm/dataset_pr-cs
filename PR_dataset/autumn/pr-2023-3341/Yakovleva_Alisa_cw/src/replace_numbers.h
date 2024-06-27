#pragma once
#include "dictionary.h"
#include "structures.h"
#include <stdlib.h>
#include <wctype.h>

void replace_numbers(struct Text text);
wchar_t* replace_not_digit(wchar_t current_wchar_of_sentence);
wchar_t* resize_result_sentence(wchar_t *str_bin_numbers, int* size);
