#pragma once
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

struct Sentence{
		wchar_t* str;
			int l;
};

struct Text{
		struct Sentence** txt;
			int l;
};
