#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "log.h"

void checkMemoryAllocation(void *ptr, const wchar_t *errorMessage)
{
    if (ptr == NULL)
    {
        logErr(L"%ls", errorMessage);
        exit(EXIT_FAILURE);
    }
}