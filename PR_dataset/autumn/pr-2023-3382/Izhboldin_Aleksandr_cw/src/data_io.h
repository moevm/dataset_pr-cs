#pragma once

// base libs
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>

// in-project libs
#include "text.h"
#include "error_handle.h"

Sentence *Sentence_read(bool *end, int *err);
Text *Text_read(int *err);
void Text_print(Text *text);