#include <locale.h>
#include "textio.h"
#include "errors.h"
#include "shift.h"
#include "chars.h"
#include "words.h"
#include "uppercase.h"
#include "function8.h"

int main(void)
{
	setlocale(LC_ALL, "");

	wprintf(L"Course work for option 5.13, created by Mikhail Orlov.\n");
	int mode;
	wscanf(L"%d", &mode);

	if (mode == 5)
	{
		wprintf(L"0 - Вывод текста после первичной обработки\n1 - Сдвиг слов в тексте на положительное число N\n3 - Подсчёт количества слов разной длины\n4 - Удаление слов, заканчивающиеся на символ в верхнем регистре\n5 - Показать это сообщение\n");
		return 0;
	}

	Text* text = ReadText();


	if (mode == 0)
	{
		PrintText(text);
	}
	else if (mode == 1)
	{
		int N;
		wchar_t* N0 = (wchar_t*)calloc(BUFSIZ, sizeof(wchar_t));
		if (N0 == NULL) ThrowError(0, N0);
		for (size_t i = 0; text->sentences[0]->words[i] != L' '; i++) N0[i] = text->sentences[0]->words[i];
		swscanf(N0, L"%d", &N);
		if (N < 0) N = 0;
		ShiftText(text, N);
	}
	else if (mode == 2)
	{
		PrintUniqueSymbols(text);
	}
	else if (mode == 3)
	{
		PrintWords(text);
	}
	else if (mode == 4)
	{
		RemoveLastUppercaseWords(text);
	}
	else if (mode == 8)
	{
		PrintSumOfNumbers(text);
	}
	else
	{
		ThrowError(1, NULL);
	}
	DeleteText(text);
	return 0;
}