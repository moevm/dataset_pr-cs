#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define START_INFO L"Course work for option 5.9, created by Anna Kadnikova.\n"
void on_startup();

void error(wchar_t* message);

wchar_t* read(wchar_t* buf);

void write(wchar_t buf);

#define HELP_MSG L"Справка о командах программе:\n0 - вывод текста после первичной обработки;\n1 - изменить все слова в тексте заканчивающиеся на “ться” так чтобы они заканчивались на “тся” и наоборот;\n2 - вывести все предложения в которых встречается второе слово первого предложения;\n3 - отсортировать предложения по возрастанию количества слов в предложении;\n4 - удалить все предложения в которых больше 10 слов;\n5 - вывести эту справку;\n9 - продублировать каждое слово в предложении (разделителем считается пробел).\n"
void print_help();