#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

struct Sentence{
    size_t len;
    long int last_index;
    wchar_t *data;
};

struct Text{
    size_t len;
    struct Sentence **data;
};

struct Dict{
    wchar_t *keys;
    wchar_t **values;
};