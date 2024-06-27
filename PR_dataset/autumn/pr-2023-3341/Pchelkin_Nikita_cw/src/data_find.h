#pragma once
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include "structs.h"

#ifndef BLOCK
#define BLOCK 100
#endif

void data_find(struct Text* text);
int wtoi(wchar_t* str);