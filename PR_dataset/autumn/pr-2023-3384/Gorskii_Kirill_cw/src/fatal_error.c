#include "fatal_error.h"
#include <stdio.h>
#include <stdarg.h> // va
#include <stdlib.h> // exit()

void fatal_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    printf("Error: ");
    vprintf(fmt, args);
    putchar('\n');

    va_end(args);
    exit(0);
}