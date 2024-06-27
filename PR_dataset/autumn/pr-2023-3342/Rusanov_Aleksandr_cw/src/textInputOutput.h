#ifndef TEXT_INPUT_OUTPUT_H
#define TEXT_INPUT_OUTPUT_H
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "struct.h"
#define RED L"\x1b[31m"
#define YELLOW L"\x1b[33m"
#define BLUE L"\x1b[34m"
#define GREEN L"\x1b[32m"
#define NONE L"\x1b[0m"

void help();
Text read_text();
void free_text(Text *text);
Sentence read_sentence(int *new_line_char_count);
void print_text(Text text);

#endif
