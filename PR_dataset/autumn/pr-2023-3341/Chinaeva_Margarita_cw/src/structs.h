#pragma once

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    wchar_t* str;
    int count_latin;
    int size_str;
} Sentence;

typedef struct {
    Sentence* sentences;
    int size_text;
} Text;
