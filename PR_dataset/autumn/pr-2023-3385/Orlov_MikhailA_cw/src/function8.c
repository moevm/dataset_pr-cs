#include <wchar.h>
#include "function8.h"
#include <stdlib.h>
#include "errors.h"

typedef unsigned long uint32_t;

#define SIZE (size_t)32

void PrintSumOfNumbers(const Text* text)
{
	uint32_t sum;
	size_t k = 0, n = 0;
	wchar_t** numbers = NULL;
	for (size_t i = 0; i < text->count; i++)
	{
		sum = n = k = 0;
		numbers = (wchar_t**)calloc(SIZE, sizeof(wchar_t*));
		if (numbers == NULL)ThrowError(0, numbers);
		size_t capacity = SIZE;
		int isNumber = 0;
		for (size_t j = 0; j < text->sentences[i]->count; j++)
		{
			if (text->sentences[i]->words[j] >= L'0' && text->sentences[i]->words[j] <= L'9')
			{
				isNumber = 1;
				if (numbers[n] == NULL) numbers[n] = (wchar_t*)calloc(SIZE, sizeof(wchar_t));
				if (numbers[n] == NULL)ThrowError(0, numbers[n]);
				numbers[n][k++] = text->sentences[i]->words[j];
			}
			else if (isNumber && (text->sentences[i]->words[j] < L'0' || text->sentences[i]->words[j]>L'9'))
			{
				isNumber = 0;
				n++;
				k = 0;
			}
		}

		for (size_t j = 0; j < n; j++)
		{
			uint32_t number;
			swscanf(numbers[j], L"%ul", &number);
			sum += number;
		}

		if (i != text->count - 1) wprintf(L"%u\n", sum);
		else wprintf(L"%u", sum);

		for (size_t j = 0; j < n; j++) free(numbers[j]);
		free(numbers);
	}
}