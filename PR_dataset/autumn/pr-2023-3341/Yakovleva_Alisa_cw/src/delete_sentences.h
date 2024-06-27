#pragma once
#include "structures.h"
#include <stdlib.h>
#include <wctype.h>

void delete_empty_sentences(struct Text* text);
void delete_sentences_with_odd_numbers(struct Text* text);
