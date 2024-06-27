#pragma once
#include <ctype.h>
#include <string.h>
#include "utils.h"

typedef char* str_t;

#define START_CAPACITY 1
str_t init_string(size_t capacity);

#define READ_WINDOW    5
str_t realloc_string(str_t str, size_t* capacity);

str_t add_to_string(str_t str, char symbol, size_t* size, size_t* capacity);

str_t convert_to_string(unsigned int num);

str_t read_sentence(size_t* size);

str_t replace(str_t original, str_t pattern, str_t replacement, size_t* size);

int is_contains(char c, str_t str, size_t size);

str_t slice(str_t str, size_t size, size_t start, size_t len);

#define SPLIT_FILTER " ,."
#define SPLIT_FILTER_LEN 3
str_t* split(str_t str, size_t size, size_t* result_size);

size_t get_return_size(str_t str, size_t size);

str_t join(str_t* strings, size_t size, size_t* result_size);

size_t sum_ord(str_t str, size_t size);

size_t find_year(str_t str, size_t size, size_t* year_length);

size_t word_count(str_t str,size_t size);