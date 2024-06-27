#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "dyn_array.h"

enum sentence_endtype {END_OF_SENTENCE = 0, END_OF_TEXT = 1};

int check_sentence(vector* text, vector* sentence);

int read_sentence(vector* text);

vector* read_text();

void print_text(vector *text);
