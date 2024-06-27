#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <wchar.h>
#include <locale.h> 
#include <wctype.h>
#define STEP 10

struct Sentence {
    wchar_t *string;
    int length;
};

struct Text {
    struct Sentence **text;
    int length;
};

typedef struct Sentence Sentence;
typedef struct Text Text;
