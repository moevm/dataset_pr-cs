#ifndef CWERROR_C
#define CWERROR_C

#include "../cwerror/cwerror.h"


void throw_error(const char *text, int return_value)
{
    printf("ERROR: %s.\nThe program has been terminated.\n", text);
    exit(return_value);
}

#endif