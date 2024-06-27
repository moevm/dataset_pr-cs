#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "ioroutine.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define ODS L"13579"

bool odd_in_sentence(struct Sentence*);
struct Text* remove_odd_text(struct Text*);