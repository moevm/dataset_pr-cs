#include <stdlib.h>
#include <wchar.h>
#include "input.h"
#include "memory.h"

#define MEMORY_CHUNK 20;

wchar_t *getTextInput(void)
{
	unsigned long end = 0, size = 0, capacity = MEMORY_CHUNK;
	wint_t ch;
	wchar_t *text = (wchar_t *)malloc(capacity * sizeof(wchar_t));
	checkMemoryAllocation(text, L"Insufficient memory for text structure");

	while ((ch = getwchar()) != WEOF && (end < 2))
	{
		if (ch == L'\n')
			end++;
		else
		{
			end = 0;
			if (size >= capacity - 1)
			{
				capacity += MEMORY_CHUNK;
				text = (wchar_t *)realloc(text, capacity * sizeof(wchar_t));
				checkMemoryAllocation(text, L"Insufficient memory for text structure");
			}
			text[size++] = (wchar_t)ch;
		}
	}
	text[size] = L'\0';
	return realloc(text, (size + 1) * sizeof(wchar_t));
}
