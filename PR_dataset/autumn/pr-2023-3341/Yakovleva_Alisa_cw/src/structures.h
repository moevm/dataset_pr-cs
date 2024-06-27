#pragma once
#include <wchar.h>
#define MEM_STEP 6
#define END_STRING '\0'

struct Sentence
{
    wchar_t *str;
    int size;
};

struct Text
{
    struct Sentence **sents;
    int number_sentences;
};
