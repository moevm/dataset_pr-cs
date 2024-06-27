#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <wctype.h>
#include <stdbool.h>
#include "structs.h"
#include "leave.h"

#define SENT_END L'\0'
#define TEXT_PIECE 10

wchar_t *read();
Sentence* record_sentence(int*, wchar_t*);
bool check_same(Text*, Sentence*);
Text* read_text();
Text* read_text_and_delete_repeats();