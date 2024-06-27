#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

// in-project libs
#include "sentence.h"
#include "text.h"
#include "data_io.h"
#include "error_handle.h"
#include "basic_processing.h"

void sort_by_latin_letters(int *err);

int count_latin_letters(Sentence *sentence);

int cmp_latin(const void *sentence1, const void *sentence2);
