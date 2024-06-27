#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define START_INFO L"Course work for option 5.11, created by Andrei Pavlov.\n"
void say_hello();

void panic(wchar_t* message);

wchar_t* read(wchar_t* buf);

void write(wchar_t buf);

#define HELP_MSG_H L"Справка о командах программе:\n"
#define HELP_MSG_0 L"0 - вывод текста после первичной обработки;\n"
#define HELP_MSG_1 L"1 - для каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер предложения в котором она встречается и количество минут до текущего времени;\n"
#define HELP_MSG_2 L"2 - в каждом предложении удалить все заглавные латинские буквы;\n"
#define HELP_MSG_3 L"3 - отсортировать предложения по уменьшению количества кириллических букв;\n"
#define HELP_MSG_4 L"4 - удалить все предложения в которых нет специальных символов (№*$#@);\n"
#define HELP_MSG_5 L"5 - вывести эту справку.\n"
#define HELP_MSG_9 L"9 - дублировать каждое слово в предложении (разделителем считается пробел).\n"
void print_help();