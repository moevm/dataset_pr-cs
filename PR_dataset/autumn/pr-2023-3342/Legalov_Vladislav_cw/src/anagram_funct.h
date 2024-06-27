#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "defines.h"
#include "structures.h"
#include "text_base_funct.h"



Text *find_anagrams(Text *text);
int **calc_char_table(Text *text);
int number_char_in_table(wchar_t ch);
