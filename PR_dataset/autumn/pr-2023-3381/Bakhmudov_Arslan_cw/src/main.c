#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>

#include "temp.h"
#include "safety.h"
#include "macros.h"
#include "config.h"
#include "struct.h"
#include "functions.h"



int main()
{
	// Locale
	char * LOCALE = setlocale(LC_ALL, "");

	// Config Variables
	wchar_t * endingchars = s_malloc(ENDINGCHARS_MAX_LEN*sizeof(wchar_t));
	int configstatus = config(endingchars);

	// Cool Stuff
	wchar_t c;
	wchar_t * curword = s_malloc(1337*sizeof(wchar_t));
	size_t wordpos = 0;
	wchar_t ** whitelist = s_malloc(1337*sizeof(wchar_t *));
	size_t wlpos = 0;

	// Info
	wprintf(L"Course work for option %ls, created by %ls.\n", CW_VARIANT, CW_AUTHOR);
	// Config status info
	/* /\/\/\
	switch(configstatus)
	{
		case (1):
			wprintf(L"[Инфо] Не обнаружен файл с настройками \"%ls\". Файл был создан заново с настройками по умолчанию.\n\n", CFG_FILENAME_INFO);
			break;
		case (2):
			wprintf(L"[Инфо] Не удалось создать файл с настройками \"%ls\". Используются настройки по умолчанию.\n\n", CFG_FILENAME_INFO);
			break;
	}
	// Instructions
	wprintf(
		L"Команды для действий с текстом:\n"
		L"0 - Вывод текста\n"
		L"1 - Подсчёт палиндромов\n"
		L"2 - Замена специальных символов\n"
		L"3 - Сортировка предложений\n"
		L"4 - Удаление смешанных предложений\n"
		L"5 - Справка о функциях программы (без ввода текста)\n"
		L"Иная цифра - выход из программы\n"
		L"Введите команду: "
	);
	/\/\/\ */
	// Task reading
	wchar_t task = L'\0';
	while (!iswdigit(task))
	{
		task = getwchar();
		secret(task);
	}

	// Newline stripper
	while (getwchar() != L'\n');
	
	// Executed task info
	//wprintf(L"\nВыбранная команда: %lc.\n", task); /\/\/\
	
	// Task router
	if (task == L'5')
	{
		f5_info();
	}
	else if (task == L'4' || task == L'3' || task == L'2' || task == L'1' || task == L'0' || task == L'9')
	{
		//wprintf(L"Введите текст (пустая строка - конец текста):\n%ls\n", SPAN); /\/\/\ .
		if (task == L'9')
		{
			c = getwchar();
			while (c != '\n')
			{
				if (c == ' ')
				{
					curword[wordpos] = '\0';
					whitelist[wlpos] = curword;
					wlpos++;
					curword = s_malloc(1337*sizeof(wchar_t));
					wordpos = 0;
				}
				else
				{
					curword[wordpos] = c;
					wordpos++;
				}
				c = getwchar();
			}
			if (wordpos > 0)
			{
				curword[wordpos] = '\0';
				whitelist[wlpos] = curword;
				wlpos++;
				curword = s_malloc(1337*sizeof(wchar_t));
				wordpos = 0;
			}
			whitelist[wlpos] = NULL;
		}

		struct Text text;
		readtext(&text, endingchars);

		if (task == L'0')
		{
			printtext(&text);
		}
		else if (task == L'1')
		{
			f1_palindromes(&text);
			printtext(&text);
		}
		else if (task == L'2')
		{
			f2_spec_char(&text);
			printtext(&text);
		}
		else if (task == L'3')
		{
			f3_sort(&text);
			printtext(&text);
		}
		else if (task == L'4')
		{
			f4_filter(&text);
			printtext(&text);
		}
		else if (task == L'9')
		{
			f9_whitelist(&text, whitelist);
			printtext(&text);
		}

		freetext(&text);
	}
	else
	{
		//wprintf(L"Выход из программы...\n"); /\/\/\ .
		int yee = 6942;
	}

	free(endingchars);
	wlpos = 0;
	while(whitelist[wlpos] != NULL)
	{
		free(whitelist[wlpos]);
		wlpos++;
	}
	free(curword);
	free(whitelist);
	return 0;
}
