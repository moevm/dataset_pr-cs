#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <time.h>
#define STEP 20
#pragma once

typedef struct Date {
    int total_time; //360*year+31*month+day
    wchar_t* year;
    wchar_t* month;
    wchar_t* day;
} Date;

typedef struct DateArray {
    Date** arr;
    int size;
    int capacity;
} DateArray;

typedef struct Sentence {
    wchar_t* sentence;
    int len_sent;
    wchar_t* first_word;
    wchar_t* last_word;
} Sentence;

typedef struct Text {
    Sentence** pr_sent;
    int count_sent;
    DateArray* slash_dates;	// DD/MM/YYYY
    DateArray* dash_dates;	// YYYY-MM-DD
    DateArray* space_dates;	// <day> <month> <year>
} Text;
