#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "cwerror.h"


void throw_error(const wchar_t *string)
{
        wprintf(L"Error: %ls.\n", string);
	exit(0);
}
