#include <stdio.h>
#include <wchar.h>

#include "memory_error.h"


void memory_error (int is_memory_ok, wchar_t *error_cause)
{
    is_memory_ok = 0;
    wprintf(L"Error: не удалось выделить память -> %ls", error_cause);
}