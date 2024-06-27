#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "other_stuff.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"

struct Sentence *make_big(struct Sentence *sentence, int max_len);
struct Text big(struct Text text, int max_len);
void all_big_words(struct Text text,int len);
