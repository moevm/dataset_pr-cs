#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <stdbool.h>

struct Sentence{
    wchar_t *data;
    size_t len;
};
typedef struct Sentence Sentence;

struct Text{
    size_t len;
    Sentence **data;
};
typedef struct Text Text;