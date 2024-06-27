#ifndef STRUCTS_H
#define STRUCTS_H
#include <wchar.h>

struct Word{
    // int count_of_symbols;
    wchar_t* word;
};

struct Sentence{
    struct Word* words;
    wchar_t* sentence;
    int quantity_of_symbols;
    int quantity_of_words;
};

struct Text{
    struct Sentence* sentences;
    int quantity_of_sentences;
};
#endif