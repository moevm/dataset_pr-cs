#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "ioroutine.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define INPUT_ERROR L"Error: Incorrect end of input\n"

wchar_t* read();
struct Sentence* read_sentence(wchar_t*, size_t);
struct Text* read_text();
bool wide_str_case_compare(const wchar_t*, const wchar_t*);
bool is_duplicate(struct Text*, struct Sentence*);
