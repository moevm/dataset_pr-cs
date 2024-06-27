#pragma once
#include <wchar.h>

struct Sentence{
    wchar_t* sentence;
    wchar_t** words;
    int num_of_words;
    int size;
};

struct Text{
    struct Sentence* text;
    int size;
};