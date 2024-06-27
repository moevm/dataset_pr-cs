#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "ioroutine.h"
#include "dict.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define DIGITS_COUNT 10
#define DIGITS L"0123456789"
#define BIN_DIGITS {L"0", L"1", L"10", L"11", L"100", L"101", L"110", L"111", L"1000", L"1001"}

struct Sentence* bin_sentence(struct Sentence*);
struct Text* bin_text(struct Text*);