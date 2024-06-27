#pragma once
#include "ioroutine.h"
#include <wctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

wchar_t* wcslow(const wchar_t* str);

int wcsincmp(const wchar_t* left, const wchar_t* right);

size_t calc_cyrillic(const wchar_t* str);

int calc_cyrillic_diff(const wchar_t* left, const wchar_t* right);

typedef struct TimeStamp {
    long hours;
    long minutes;
} TimeStamp;

TimeStamp get_current_time();

bool is_zeros(wchar_t* str, size_t size);

#define HOURS_MAX 23
#define MINUTES_MAX 59
bool check_is_time(wchar_t* str);

TimeStamp* realloc_search_results(TimeStamp* buf, size_t* buf_size);

#define TIMESTAMP_MIN_STR_LEN 5
#define END_OF_RESULTS -1
void* find_times(wchar_t* str, size_t size);

void print_times(void* times, size_t line_number);

wchar_t* delete_big_latin(wchar_t* str, size_t* size);

#define SPEC_FILTER L"№*$#@"
#define SPEC_FILTER_SIZE 5
bool is_contains(wchar_t c, wchar_t* str, size_t size);

bool have_spec_symbols(wchar_t* str, size_t size);

wchar_t* make_copy(wchar_t* str, size_t size);

wchar_t* make_joinable(wchar_t* str, size_t size);

wchar_t* update_copy_buffer(wchar_t* buf, size_t* buf_size, wchar_t* word_to_add, size_t word_size);

wchar_t* copy_words(wchar_t* str, size_t* size);
