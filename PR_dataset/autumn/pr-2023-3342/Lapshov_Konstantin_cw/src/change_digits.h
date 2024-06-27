#pragma once
#include "structures.h"

void change_digits(struct Text *text);
void get_digit_occurrences(struct Text *text, struct Unique_Word numbers[]);
void change_digit_for_occurrences(struct Text *text, struct Unique_Word numbers[]);

long get_digit_from_str(wchar_t letter);
wchar_t* insert_wchar(wchar_t* str, int position, const wchar_t* newChars);