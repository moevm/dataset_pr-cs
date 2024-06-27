#pragma once
#include "struct_define.h"
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct Sentence *get_sentence();
struct Text get_text();
void additional_task();

struct Text delete_same_sentance();
struct Sentence *fix_sentence();
struct Sentence *find_and_insert();
struct Text replace_words();
struct Text delete_same_start_end();

struct Result find_date_in_sentance();
int date_sort();
void print_sorted_dates();
struct Date now_day();
void happened_dates();



