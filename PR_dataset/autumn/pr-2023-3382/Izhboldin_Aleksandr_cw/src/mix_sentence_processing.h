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

void delete_mixed_sentence(int *err);

bool check_sentence_if_mixed(Sentence *sentence, int *err);

bool check_word_if_mixed(wchar_t *word);