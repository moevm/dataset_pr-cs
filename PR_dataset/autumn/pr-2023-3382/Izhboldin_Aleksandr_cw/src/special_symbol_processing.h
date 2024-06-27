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

#define SPECIAL_SYMBOLS L"№*$#@.,;"
#define STR_TO_REPLACE L">special symbol<"

void change_special_symbols(int *err);