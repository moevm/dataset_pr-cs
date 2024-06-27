#pragma once

#ifndef _TEXT_H
#define _TEXT_H

#include <stdlib.h>
#include <stdbool.h>

#include "sentence.h"

typedef size_t Tsize_t;

#define DEFAULT_TEXT_END DEFAULT_END

typedef struct
{
    Sentence_t **data;
    Tsize_t len;
    Tsize_t capacity;
    wchar_t end;

} Text_t;

Text_t *init_text();

void free_text(Text_t *);

Sentence_t *get_sentence(Text_t *, Tsize_t);

Text_t *add_sentence(Text_t *, Sentence_t *);

Text_t *delete_sentence(Text_t *, Tsize_t);

#endif // _TEXT_H
