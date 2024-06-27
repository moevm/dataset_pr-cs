#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

struct Sentence{
	int len;
	wchar_t *str;
};

struct Text{
	int n;
	struct Sentence **sents;
};

struct Dictionary{
	wchar_t key[70];
	wchar_t value[70];
};
