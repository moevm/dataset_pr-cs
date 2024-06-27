#pragma once
#include <wchar.h>
#include <wctype.h>

typedef struct Sentence
{
    wchar_t *chars;
    int len;
    int cap;
} Sentence;

Sentence *create_sentence();
void extend_sentence(Sentence *sentence);
void free_sentence(Sentence *sentence);
void push_sentence(Sentence *sentence, wchar_t *ch);
void print_sentence(Sentence *sentence);
int replace_n_at_index_sentence(Sentence *sentence, wchar_t *source, int n, int i);
