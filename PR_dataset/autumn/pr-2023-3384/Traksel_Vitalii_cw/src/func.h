#pragma once
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

struct Sentence {
	wchar_t ** words;
	wchar_t * symbols;
	int num_sym;
	int num_words;
};

struct Text {
	struct Sentence ** sent;
	int num_sent;
};

wchar_t * sample(struct Text * text);
wchar_t * first_upper(struct Text * text);
wchar_t * vowel_sort(struct Text * text);
int isvowel(wchar_t letter);
wchar_t * num_repeat(struct Text * text);
void del_repeat (struct Text * txt);
void free_text(struct Text * text);
void func8(struct Text * text);
