#ifndef CW_TEXT_H
#define CW_TEXT_H

#include <stdlib.h>
#include "string.h"

typedef struct {
    string_t *sentences;
    size_t len;
    size_t capacity;
} text_t;

typedef int (*text_filter_func_t)(text_t *text, string_t *str, void *user_ptr);

void       text_init(text_t *text);
void       text_deinit(text_t *text);
string_t  *text_extend(text_t *text);
void       text_shrink(text_t *text);
void       text_filter(text_t *text, text_filter_func_t rule, void *user_ptr);

#endif