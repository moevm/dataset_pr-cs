#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>
#include <wctype.h>

struct Text{
	wchar_t **text;
    int len;
};

struct Sentence{
	wchar_t *sent;
	int len;
};

