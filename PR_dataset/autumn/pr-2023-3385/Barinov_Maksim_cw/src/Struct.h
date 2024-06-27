#pragma once

struct Sentence{
	wchar_t* symbols;
	int size;
	int ends;
};

struct Text{
	struct Sentence** sents;
	int cnt;
};
