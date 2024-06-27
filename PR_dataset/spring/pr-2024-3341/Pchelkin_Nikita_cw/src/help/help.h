#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

void print_help();
void raise_error(char* reason);
void raise_reading_error(char* reason);
void info(Png* image);