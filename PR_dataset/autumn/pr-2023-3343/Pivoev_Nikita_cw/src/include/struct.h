#ifndef STRUCT_H
#define STRUCT_H

#include <wchar.h>

typedef struct {
    wchar_t* words;
    int size;
} Sentence;

typedef struct {
    Sentence* sentences;
    int size;
} Text;

#endif