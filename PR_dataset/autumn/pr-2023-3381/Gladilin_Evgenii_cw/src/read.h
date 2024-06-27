#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "other_stuff.h"
#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define INPUT_ERROR L"Error: Incorrect end of input\n"

int check_for_duplicates(struct Sentence **text, struct Sentence *sentence, int n);
struct Sentence *read_sentence();
struct Text read_text();

