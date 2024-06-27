#pragma once

#ifndef _CHAR_STRUCT_H
#define _CHAR_STRUCT_H

#include <stdlib.h>
#include <wchar.h>

#include "mathfuncts.h"

#define DEFAULT_CAPACITY 1
#define DEFAULT_LEN 0
#define DEFAULT_CAPACITY_INCREASE_COEFFICIENT 1.5
#define DEFAULT_END 0

typedef struct
{
    void *data;
    size_t len;
    size_t capacity;
    wchar_t end;

} Char_struct;

Char_struct *init_char_struct();

void free_char_struct(Char_struct *);

void _increase_capacity_char_struct(Char_struct *, size_t);

#endif // _CHAR_STRUCT_H
