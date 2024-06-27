#pragma once

#include "ioroutine.h"
#include "sentence.h"
#include <stdbool.h>



typedef struct Text {
    size_t size;
    size_t capacity;
    size_t fib_last;
    Sentence** data;
} Text;



Text* reallocate_text(Text* text);

Text* init_text();

Text* free_text(Text* text);

Text* add(Text* text, Sentence* sent);

Text* read_text();

Text* optimize(Text* text);

Text* save_only_unique(Text* text, int (*comp)(const wchar_t *, const wchar_t *));

void find_and_print(Text* text, void* (*finder)(wchar_t *, size_t), void (*printer)(void *, size_t));

Text* apply(Text* text, wchar_t * (*func)(wchar_t *, size_t*));

#define DECLARE_COMPARATOR_ADAPTER(comp) int comparator_adapter(const void* left, const void* right) { \
    const Sentence** _Left = (const Sentence**)left; \
    const Sentence** _Right = (const Sentence**)right; \
    return comp((*_Left)->data, (*_Right)->data); \
};

Text* sort(Text* text, int (*comp)(const wchar_t *, const wchar_t *));

Text* filter(Text* text, bool (*func)(wchar_t *, size_t));
