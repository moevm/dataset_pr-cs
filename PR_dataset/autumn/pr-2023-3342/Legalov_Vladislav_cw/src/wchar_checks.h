#pragma once
#include <wchar.h>
#include <ctype.h>
#include "structures.h"

int is_alpha_upper_ru_en(wchar_t ch);
wchar_t to_lower_ru_en(wchar_t ch);
int check_wchars_equality(wchar_t first, wchar_t second);
void get_next_alpha(wchar_t source, wchar_t *res_first, wchar_t *res_second);


