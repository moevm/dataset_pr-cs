#pragma once
#include "structures.h"
#include <stdlib.h>
#include <wctype.h>

struct Sentence* read_sentence();
struct Text read_text();
int chek_end_of_text(wchar_t *buf, int* number_stop, int* sentence_length);
void resize_sentence(wchar_t *buf, int* size);
