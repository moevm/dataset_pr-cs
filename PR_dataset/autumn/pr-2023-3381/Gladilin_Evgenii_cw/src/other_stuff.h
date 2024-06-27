#pragma once
#include <wchar.h>
#include <stdlib.h>
#include "structs.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"

void freeText(struct Text t);
wchar_t *get_value(struct Dictionary dict[], int size, wchar_t *key);
void fail(wchar_t *message);
void text_print(struct Text t);
