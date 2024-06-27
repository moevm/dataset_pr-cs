#include "error_handle.h"

void my_error(wchar_t *str, int *err)
{
    wchar_t buffer[256];
    wcscpy(buffer, str);
    switch (*err)
    {
        case WRONG_FUNCTION_ERROR:
            wcscat(buffer, L": Wrong function");
            break;
        case INDEX_ERROR:
            wcscat(buffer, L": Index out of range");
            break;
        case MEMORY_ALLOC_ERROR:
            wcscat(buffer, L": Memory allocation error");
            break;
    }

    wprintf(L"%ls\n", buffer);
}


