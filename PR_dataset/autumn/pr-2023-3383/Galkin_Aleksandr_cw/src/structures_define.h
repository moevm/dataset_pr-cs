#ifndef STRUCTURES
#define STRUCTURES
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <wctype.h>
#define STEP 8

struct Sentence
{
    wchar_t *sentence;
    size_t str_length;
    size_t words_count;
};
struct Text
{
    struct Sentence **text;
    size_t length;
};
struct Date
{
    int day;
    int month;
    int year;
};

#endif