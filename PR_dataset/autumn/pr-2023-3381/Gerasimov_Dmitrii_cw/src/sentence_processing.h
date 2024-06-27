#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <time.h>
#include "dyn_array.h"


void option0(vector* text);

void option1(vector* text);

void option2(vector* text);

void option3(vector* text);

void option4(vector* text);

void option5();

void option9(vector* text, size_t word_len);

void free_text(vector* text);

int cmpOpt_1(const void *a, const void* b, size_t _);

int get_time_from_sentence(size_t index, vector *sentence, struct tm *start);

int cmpOpt2(const void* a, const void* b, size_t _);

int cmpOpt3_2(const void* a, const void* b, size_t el_size);

int cmpOpt3_1(const void* a, const void* b);

int cmpOpt4_1(const void* a, const void* b, size_t _);

int cmpOpt9(const void* a, const void* b, size_t _);