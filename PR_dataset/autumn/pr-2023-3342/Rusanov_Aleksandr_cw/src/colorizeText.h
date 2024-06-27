#ifndef COLORIZE_H
#define COLORIZE_H

#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include "textHandle.h"
#include "struct.h"

#define RED L"\x1b[31m"
#define YELLOW L"\x1b[33m"
#define BLUE L"\x1b[34m"
#define GREEN L"\x1b[32m"
#define NONE L"\x1b[0m"

void print_color(Sentence sentence, int start_index, int end_index, const wchar_t *color);
void colorize_words(Text *text);
#endif
