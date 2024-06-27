#ifndef STRUCTS_HEADER
#define STRUCTS_HEADER
#include <wchar.h>
#include <stdlib.h>

struct Sentence{
	size_t length;
	int last_index;
	wchar_t * sentence;
};

typedef struct Sentence Sentence;

struct Text{
	size_t length;
	Sentence ** text;
};

typedef struct Text Text;

#endif
