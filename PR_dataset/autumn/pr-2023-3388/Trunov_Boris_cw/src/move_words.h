#ifndef MOVE_WORDS_HEADER
#define MOVE_WORDS_HEADER

#include <wchar.h>
#include <stdlib.h>
#include "structs.h"

#define SEPARATOR L" .,"

void move_words(Text* text, size_t count_inverse);

#endif
