#pragma once

#include <wchar.h>

#define WRONG_FUNCTION_ERROR 1
#define INDEX_ERROR 2
#define MEMORY_ALLOC_ERROR 3

void my_error(wchar_t *str, int *err);
