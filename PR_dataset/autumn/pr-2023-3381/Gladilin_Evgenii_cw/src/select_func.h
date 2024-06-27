#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "read.h"
#include "structs.h"
#include "all_translitiration.h"
#include "all_special_sym.h"
#include "all_bin_text.h"
#include "delete_odd.h"

#define FUNC_INFO L"0 - вывод текста после первичной обработки\n1 - транслитерация всех кириллических символов в тексте. Например, подстрока “Какой nice пень” должна принять вид “Kakoj nice pen’” (использовать ГОСТ 7.79-2000)\n2 - вывод всех специальных символов в порядке уменьшения их кода\n3 - заменить все цифры в тексте их двоичным кодом\n4 - удалить все предложения, в которых есть нечётные цифры\n5 - справка\n"
#define MEM_ERROR L"Error: Failed to allocate memory\n"

void num_scan();
void choice_func(int n);
void all_transliteration();
void all_special_sym();
void all_bin_sym();
void all_delete_odd();
void func_info();
