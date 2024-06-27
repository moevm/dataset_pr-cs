#pragma once

#ifndef _SENTENCE_H
#define _SENTENCE_H

#include <stdlib.h>
#include <stdbool.h>

#include "word.h"

typedef size_t Ssize_t;

#define DEFAULT_SENTENCE_END DEFAULT_END

typedef struct
{
    Word_t **data;
    Ssize_t len;
    Ssize_t capacity;
    wchar_t end;

} Sentence_t;

Sentence_t *init_sentence();

void free_sentence(Sentence_t *);

Word_t *get_word(Sentence_t *, Ssize_t);

Sentence_t *add_word(Sentence_t *, Word_t *);

bool compare_sentences(Sentence_t *, Sentence_t *, bool);

Sentence_t *delete_word(Sentence_t *, Ssize_t);

#endif // _SENTENCE_H
