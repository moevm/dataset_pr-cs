#pragma once
#include <wchar.h>

struct sentence{
    wchar_t** words;
    size_t word_count;
    size_t lenght;
    size_t last_sentence; // 0 if not, else 1
};

typedef struct sentence sentence;

struct text{
    sentence** sentences;
    size_t lenght;
};

typedef struct text text;
