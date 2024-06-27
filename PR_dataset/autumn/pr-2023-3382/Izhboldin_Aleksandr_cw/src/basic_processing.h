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

void print_basic_processed_text(int *err);

Text *basic_processing(Text *text, int *err);