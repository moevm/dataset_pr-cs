#pragma once
#include <wchar.h>
struct Word{
	wchar_t* p;
	int len;
	int k;
};


struct Sentence{
	struct Word* p;
	int len;
};


struct Text{
	struct Sentence* p;
	int size;
};

