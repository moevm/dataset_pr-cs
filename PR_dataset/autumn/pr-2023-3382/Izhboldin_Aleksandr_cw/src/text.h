#pragma once
// base libs
#include <stdlib.h>
#include <wchar.h>

// in-project libs
#include "sentence.h"
#include "error_handle.h"

#define TEXT_BUFFER 32

typedef struct
{
    size_t size;
    size_t memsize;
    Sentence **sentences;
} Text;

Text *Text_create(int *err);
void Text_delete(Text **text);
void Text_add_sentence(Text *text, Sentence *sentence, int *err);
Text *Text_recreate(Text *text, int *err);
