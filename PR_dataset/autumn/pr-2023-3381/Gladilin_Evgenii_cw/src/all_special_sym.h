#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "other_stuff.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"

int cmp(const void *a, const void *b);
struct Sentence  *make_special(struct Sentence *sentence);
struct Text special(struct Text text);
void all_special_sym(struct Text text);
