#pragma once

#include <strings.h>
#include "str.h"

typedef str_t* text_t;

text_t sort_text(text_t text,size_t size_text);

int cmp(const void* first_str,const void* second_str);

text_t init_text(size_t capacity, size_t** str_sizes);

text_t realloc_text(text_t text, size_t* capacity, size_t** str_sizes);

text_t add_to_text(text_t text, str_t str, size_t str_size, size_t** str_sizes, size_t* size, size_t* capacity);

text_t read_text(size_t* size, size_t** str_sizes);

text_t defragmentate(text_t text, size_t* size, size_t** str_sizes);

text_t unique(text_t text, size_t* size, size_t** str_sizes);

text_t replace_dates(text_t text, size_t* size, size_t** str_sizes);

text_t color_words(text_t text, size_t* size, size_t** str_sizes);

text_t delete_with_same_begin_end(text_t text, size_t* size, size_t** str_sizes);

int first_word_code_sum_comparator(const void* left, const void* right);

text_t update_sizes(text_t text, size_t* size, size_t** str_sizes);

text_t sort_by_codes(text_t text, size_t* size, size_t** str_sizes);
