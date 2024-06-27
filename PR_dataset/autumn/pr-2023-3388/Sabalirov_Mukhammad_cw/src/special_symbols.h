#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "ioroutine.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define SYMBOLS L"№*$#@"

int cmp (const void*, const void*);
struct Sentence* special_sentence(struct Sentence*);
struct Text* special_text(struct Text*);
