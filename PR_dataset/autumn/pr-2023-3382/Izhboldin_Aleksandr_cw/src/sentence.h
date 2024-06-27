#pragma once
// base libs
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

// in-project libs
#include "error_handle.h"

#define SENTENCE_BUFFER 32

typedef struct
{
    size_t size;
    size_t memsize;
    wchar_t *sentence;
} Sentence;

Sentence *Sentence_create(int *err);
void Sentence_delete(Sentence **sentence);
void Sentence_add_symbol(Sentence *sentence, wchar_t symbol, int *err);
void Sentence_add_word(Sentence *sentence, wchar_t *word, int *err);
void Sentence_replace_symbol(Sentence *sentence, size_t index, wchar_t new_symbol, int *err);
Sentence *Sentence_copy(Sentence *sentence, int *err);
