#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"



typedef struct {
    size_t size;
    size_t capacity;
    char* data;
} string;


string* create_empty();

string* resize(string* str);

string* push(string* str, const char symbol);

string* str_from_char(const char symbol);

string* str_from_buffer(const char* buffer);

string* copy(string* original);

string* slice(string* input, size_t start, size_t end);

#define NOT_FOUND (size_t) -1
size_t find(string* haystack, string* needle, size_t start);

void compute_lps(string* needle, int lps[]);

string** split(string* str, string* delimeter, size_t* output_size);

bool equal(string* left, string* right);

bool startswith(string* str, string* prefix);

bool is_num(string* str);

int64_t stoi(string* str);

#endif /* STR_H */
