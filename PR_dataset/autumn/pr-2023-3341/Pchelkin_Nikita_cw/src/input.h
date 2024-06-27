#pragma once
#include <stdlib.h>
#include <wchar.h>
#include "structs.h"
#include "error.h"

#ifndef BLOCK
#define BLOCK 100
#endif

void split_sentence(struct Sentence* sent);
wchar_t sent_input(struct Sentence* new_sentence);
void text_input(struct Text* text);
