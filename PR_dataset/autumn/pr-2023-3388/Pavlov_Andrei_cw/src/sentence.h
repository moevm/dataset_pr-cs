#pragma once
#include "ioroutine.h"


typedef struct Sentence {
    size_t size;
    size_t capacity;
    size_t last_capacity;
    wchar_t* data;
} Sentence;

Sentence* reallocate_sentence(Sentence* sent);

Sentence* init_sentence();

Sentence* free_sentence(Sentence* sent);

Sentence* append(Sentence* sent, wchar_t symbol);

Sentence* read_sentence();

