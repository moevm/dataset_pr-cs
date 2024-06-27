#ifndef CW_INPUT_OUTPUT_H
#define CW_INPUT_OUTPUT_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "structs.h"

Sentence input_sentence(int* end_counter);
Text input_text();
void print_help();
void print_text();

#endif
