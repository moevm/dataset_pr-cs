#pragma once

#ifndef _WORD_H
#define _WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "char_struct.h"

typedef size_t Wsize_t;

#define DEFAULT_WORD_END DEFAULT_END

typedef struct
{
    wchar_t *data;
    Wsize_t len;
    Wsize_t capacity;
    wchar_t end;

} Word_t;

Word_t *init_word();

void free_word(Word_t *);

Word_t *copy_word(const Word_t *);

wchar_t get_char(Word_t *, Wsize_t);

Word_t *add_char(Word_t *, wchar_t);

Word_t *add_str(Word_t *, const wchar_t *);

bool compare_words(Word_t *, Word_t *, bool);

bool is_number(Word_t *);

#endif // _WORD_H
