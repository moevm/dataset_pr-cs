#pragma once
#include <wchar.h>
#include <wctype.h>

typedef struct Word
{
    wchar_t *chars;
    int length;
    int capacity_chars;
} Word;

void initial_word(Word *word);
Word *make_word();
void expand_word(Word *word);
void free_word(Word *word);
int word_comparison(const Word *str1, const Word *str2);