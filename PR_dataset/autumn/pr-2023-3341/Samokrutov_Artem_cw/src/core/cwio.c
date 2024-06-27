#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "cwerror.h"
#include "cwfuncs.h"
#include "cwio.h"
#include "cwstructures.h"


void print_cw_info(void)
{
        wprintf(L"Course work for option %ls, created by %ls %ls.\n", CW_OPTION, FIRST_NAME, LAST_NAME);
}

void print_Text(Text *text)
{
	for (int i = 0; i < text->len; i++) {
		wprintf(L"%ls.\n", text->sentences[i].characters);
	}
}

void get_task(int *task)
{
        if (wscanf(L"%d", task) == 0) {
                throw_error(TASK_ERR_MSG);
                *task = -1;
        }
}

wchar_t *read(int *sep_count)
{
        int text_len = 0;
        int capacity = 0;
        wchar_t *text = NULL;

        int termination_symbol_count = 0;
	wchar_t ch = getwchar();
        while (termination_symbol_count < wcslen(TERMINATION_SEQUENCE)) {
                ch = getwchar();

                if (ch == WEOF){
                        throw_error(NO_TERMINATION_SEQUENCE_ERR_MSG);
                } else if (ch == TERMINATION_SEQUENCE[termination_symbol_count]) {
                        termination_symbol_count++;
                } else {
                        termination_symbol_count = 0;
                }

                if (text_len + 1 >= capacity) {
                        capacity += CHUNK;
                        text = (wchar_t *)realloc(text, capacity * sizeof(wchar_t));

			if (text == NULL)
				throw_error(MEMORY_ERR_MSG);
                }

                if (wcschr(SENTENCE_SEPARATORS, ch)) {
                        (*sep_count)++;
                }

                text[text_len++] = ch;
        } 
	
	if (!wcschr(SENTENCE_SEPARATORS, text[text_len - 1 - wcslen(TERMINATION_SEQUENCE)]))
                throw_error(FORMAT_ERR_MSG);

	for (int i = 1; i <= wcslen(TERMINATION_SEQUENCE); i++)
		text[text_len - i] = STRING_TERMINATOR;

	if (wcslen(text) <= 1)
		throw_error(NO_INPUT_ERR_MSG);

        return text;
}

void help()
{
	wprintf(L"Программа реализует следующие функции:\n");
	wprintf(L"\t0) Вывод текста после первичной обработки :каждое предложение выводится с новой строки; повторяющиеся (с точностью до регистра букв) предложения удалены.\n");
	wprintf(L"\t1) Вывести для каждого предожения строку-дату вида \"ДД-ММ-ГГГГ\", где день - количество слов в предложении, месяц - наибольшая длина слова в предложении, год - общее количество символов в предложении + 1900.\n");
	wprintf(L"\t2) Вывести предложения так, чтобы слова шли в обратном порядке.\n");
	wprintf(L"\t3) Отсортировать предложения по длине первого слова в предложении.\n");
	wprintf(L"\t4) Удалить все предложения, у которых все слова имеют длину не больше 3 символов.\n");
	wprintf(L"\t5) Вывести справку о функция, которые реализует программа.\n");
	wprintf(L"Каждое предложения выводится с новой строки. Для выбора функции при запуске программы введите число, соответствующее функции (0, 1, 2, 3, 4 или 5).\n");
	wprintf(L"Признаком конца текста считается двойной перенос строки. Любой текст введённый после этого будет игнорирован.\n");
}
