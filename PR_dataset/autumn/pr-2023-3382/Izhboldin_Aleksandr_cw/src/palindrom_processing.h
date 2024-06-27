#pragma once
// base libs
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>

// in-project libs
#include "sentence.h"
#include "text.h"
#include "data_io.h"
#include "error_handle.h"
#include "basic_processing.h"

#define DELIMITERS L" ,.\n\t"

void check_text_on_palindromes(int *err);

int check_sentence_on_palindromes(Sentence *sentence);

bool is_palindrome(wchar_t *word);
