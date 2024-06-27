#pragma once
#include <wchar.h>

typedef struct {
	wchar_t* symbols;
	size_t count;
	size_t len;
} Sentence;

typedef struct {
	Sentence **sent;
	size_t tlen;
	size_t teklen;
} Text;
