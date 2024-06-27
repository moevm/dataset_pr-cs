#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#define MEM_STEP 4

struct Text{
    wchar_t** sentences;
    int size;
};
struct Sentence{
    wchar_t* str;
    int size_sent;
};
#endif
