#pragma once
#include "console.h"


typedef struct Sentence {
    size_t size;
    size_t capacity;
    wchar_t* data;
} Sentence;

#define ALLOC_SENT 10
Sentence* realloc_sentence(Sentence* sent);

Sentence* sentence_initialization();

Sentence* sentence_free(Sentence* sent);

Sentence* add_symbol(Sentence* sent, wchar_t s);

Sentence* read_sentence();

Sentence* double_word(Sentence* sent);

