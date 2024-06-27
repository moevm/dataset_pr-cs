#pragma once
#include <wchar.h>

typedef struct Sentence
{
	wchar_t* words;
	size_t count;
} Sentence;

typedef struct Text
{
	Sentence** sentences;
	size_t count;
} Text;