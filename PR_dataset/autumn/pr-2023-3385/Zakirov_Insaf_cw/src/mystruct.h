#pragma once

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

typedef struct Sentence{
    wchar_t* symbol;
    int count;
} Sentence;

typedef struct Text {
    Sentence* sentence;
    int count;
} Text;

void inittext(Text* text);
