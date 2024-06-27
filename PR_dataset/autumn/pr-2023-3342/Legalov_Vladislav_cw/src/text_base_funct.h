#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "defines.h"
#include "structures.h"
#include "wchar_checks.h"


void text_append(Text *text, Sentence *sentence);
void free_sentence(Sentence *sentence);
void free_text(Text *text);

Text* create_text_with_copyed_pointers(Text* source);
void text_delete_repeat(Text *text);
void sort_text(Text *text);
int comparator_upper_alpha(const void* first, const void* second);
