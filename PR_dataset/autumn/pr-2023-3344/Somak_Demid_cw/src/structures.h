#pragma once

#include <wchar.h>


typedef wchar_t wchar;

typedef struct Sentence
{
    wchar **arrofwords;
    unsigned countwords;
    wchar *arrofseps;
    unsigned countseps;
    unsigned sentlen;
} Sentence;


typedef struct Text
{
    Sentence **arrofsents;
    unsigned countsents;
} Text;
