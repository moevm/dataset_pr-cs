#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "other_stuff.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"

int check_for_odd(struct Sentence *sentence);
struct Text odd(struct Text text);
void all_delete_odd(struct Text text);
