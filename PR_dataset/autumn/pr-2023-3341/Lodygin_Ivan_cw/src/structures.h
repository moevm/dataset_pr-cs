#ifndef LENTHIRD_H
#define LENTHIRD_H

#include <wchar.h>

struct Sentence{
    wchar_t *str;
    int size;
};

struct Text{
    struct Sentence **sents;
    int n;
    int size;
};

struct Sentence* read_sentence();
struct Text read_text();

#endif