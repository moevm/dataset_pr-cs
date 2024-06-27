#pragma once
#include "console.h"
#include <wctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

wchar_t* lower(const wchar_t* str);

int compare(const wchar_t* left, const wchar_t* right);

wchar_t** realloc_results_buffer(wchar_t** buf, size_t* buf_size);

wchar_t* make_word_copy(wchar_t* source, size_t len);

wchar_t** update_results_buffer(wchar_t** buf, size_t* buf_size, wchar_t* word);

wchar_t** split(wchar_t* str, size_t size);

int compare_words_count(wchar_t* left, wchar_t* right);

wchar_t* replace(wchar_t* original, wchar_t* pattern, wchar_t* replacement);

wchar_t* fix_endings(wchar_t* original, size_t* size);

wchar_t* find_and_print(wchar_t* original, wchar_t* pattern, size_t* size);

#define SPEC_FILTER L"№*$#@"
#define SPEC_FILTER_SIZE 5
bool is_contains(wchar_t symbol, wchar_t* str, size_t size);

bool longer_than_ten(wchar_t* str, size_t size);
