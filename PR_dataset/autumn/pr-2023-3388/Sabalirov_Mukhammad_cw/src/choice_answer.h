#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "read.h"
#include "structs.h"
#include "ioroutine.h"
#include "cyrillic.h"
#include "special_symbols.h"
#include "replace_to_binary.h"
#include "remove_odd.h"
#include "free.h"
#include "double.h"

#define FUNC_INFO L"<Номер функции>. <Действие функции>.\n0. Вывод текста после первичной обработки (программа должна найдет и удалит все повторно встречающиеся предложения, сравнивая их посимвольно, но без учета регистра).\n1. Сделать транслитерацию всех кириллических символов в тексте. Например, подстрока “Какой nice пень” примет вид вид “Kakoj nice pen`” (ГОСТ 7.79-2000).\n2. Для каждого предложения вывести все специальные символы (№*$#@) в порядке уменьшения их кода.\n3. Заменить все цифры в тексте их двоичным кодом.\n4. Удалить все предложения в которых есть нечетные цифры.\n5. Справка.\n"
#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define FUNC_NUM_ERROR L"Error: Wrong number of function\n"
#define OUT_STR L"%ls\n"

void choice_func();
void print_text(struct Text*);
void make_all_for_translit(struct Text *text);
void make_all_for_special(struct Text *text);
void make_all_for_bin(struct Text *text);
void make_all_for_odd(struct Text *text);
void make_all_for_double(struct Text *text);