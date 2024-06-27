#include <wchar.h>

#ifndef STRUCT
#define STRUCT

struct Sentence
{
	wchar_t *words;
	int len;
	int cyrillic_symbol_count;
};

struct Text
{
	struct Sentence *sentences;
	int len;
};
#endif
