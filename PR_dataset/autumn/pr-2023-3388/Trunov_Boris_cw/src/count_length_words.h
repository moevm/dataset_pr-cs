#ifndef COUNT_LENGTH_WORDS_HEADER
#define COUNT_LENGTH_WORDS_HEADER

#include <wchar.h>
#include <stdlib.h>
#include "structs.h"
#define SIZE_WORDS 100
#define SEPARATOR L" .,"
#define BUFFSIZE 2000

void count_length_words(Text * text);

#endif
