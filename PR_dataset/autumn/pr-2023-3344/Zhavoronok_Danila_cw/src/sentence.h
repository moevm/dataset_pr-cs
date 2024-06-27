#pragma once
#include <wchar.h>
#include <wctype.h>
typedef struct Sentence
{
    wchar_t *text;
    int length;
    int capacity;
    int counter;
} sentence;

void init_sentence(sentence *);
void free_sentence(sentence *);
void enlarge_sentence(sentence *);
void enlarge_sentence_if_needed(sentence *);
sentence *create_sentence();
void append_wchar_to_sentence(sentence *, wchar_t *);
void print_sentence(sentence *);
int comp_sentences(sentence *, sentence *, int is_case_sensitive);
