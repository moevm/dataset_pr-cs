#include "text.h"
#include <stdio.h>
#include "fatal_error.h"

#define TEXT_BLOCKSIZE 8

void text_init(text_t *text)
{
    text->len = 0;
    text->capacity = TEXT_BLOCKSIZE;
    text->sentences = (string_t*)malloc(text->capacity * sizeof(string_t));
    if (text->sentences == NULL)
        fatal_error("failed to allocate %ld bytes.", (text->capacity * sizeof(string_t)));
}

void text_deinit(text_t *text)
{
    for (size_t i = 0; i < text->len; i++)
        string_deinit(&text->sentences[i]);
    free(text->sentences);
}

string_t *text_extend(text_t *text)
{
    if (text->capacity == text->len) {
        text->capacity *= 2;
        text->sentences = (string_t*)realloc(text->sentences, text->capacity * sizeof(string_t));

        if (text->sentences == NULL)
            fatal_error("failed to reallocate %ld bytes.", (text->capacity * sizeof(string_t)));
    }

    return &text->sentences[text->len++];
}

void text_shrink(text_t *text)
{ 
    //text->capacity = 1 << (64 - __builtin_clzl(text->len - 1)); // good alternative?????
    text->capacity = text->len;
    text->sentences = (string_t*)realloc(text->sentences, sizeof(string_t)*text->capacity);

    if (text->sentences == NULL)
        fatal_error("failed to reallocate %ld bytes.", (text->capacity * sizeof(string_t)));
}

void text_filter(text_t *text, text_filter_func_t rule, void *user_ptr)
{
    string_t *out = text->sentences;
    string_t *end = text->sentences + text->len;

    for (string_t *in = text->sentences; in != end; in++) {
        if (rule(text, in, user_ptr)) {
            *out = *in;
            out++;
        }
        else {
            string_deinit(in);
        }
    }

    text->len = (out - text->sentences);
    text_shrink(text);
}