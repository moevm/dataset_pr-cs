#pragma once
#include "structures.h"
#include "deleteSent.h"
#include <wchar.h>
#include <wctype.h>
#include <string.h>


void firstProc(Text* text);
int wcsnotregsenscmp(wchar_t* sent1, wchar_t* sent2);