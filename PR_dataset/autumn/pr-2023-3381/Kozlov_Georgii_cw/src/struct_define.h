#pragma once
#include <wchar.h>

struct Sentence
{
    wchar_t *str;
    int len;
};

struct Text
{
    struct Sentence **text;
    int len;    
};

struct Date
{
    int day;
    int month;
    int year;
};

struct Result
    {
        struct Date *dates;
        int len;    
    };
