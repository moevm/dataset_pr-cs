#pragma once
#include <wchar.h>

struct Sentence 
{
    wchar_t *sentence;
    int len;
    int capacity;
};

struct Text
{
    struct Sentence *text;
    int count;
};
