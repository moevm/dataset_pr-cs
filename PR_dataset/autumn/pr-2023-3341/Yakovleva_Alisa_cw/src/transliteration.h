#pragma once
#include "structures.h"
#include "dictionary.h"
#include <stdlib.h>
#include <wctype.h>

void transliteration(struct Text text);
wchar_t* resize_transletiration_sentence(wchar_t *str_transliteration, int* size);
