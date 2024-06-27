#include "error.h"

#include <stdio.h>
#include <stdlib.h>

#define ERROR_STD stdout

void ERROR(char* message, int code) {
    fprintf(ERROR_STD, "Error: %s\n", message);
    exit(code);
}
