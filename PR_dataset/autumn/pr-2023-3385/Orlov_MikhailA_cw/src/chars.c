#include "chars.h"
#include "structs.h"
#include "errors.h"

#define BLOCK_SIZE (size_t)32

void PrintUniqueSymbols(const Text* text)
{
	size_t capacity = BLOCK_SIZE;
	size_t n = 0;
	wchar_t* chars = (wchar_t*)calloc(capacity, sizeof(wchar_t));
	if (chars == NULL) ThrowError(0, chars);
	for (size_t i = 0; i < text->count; i++)
	{
		const Sentence* s = text->sentences[i];
		for (size_t j = 0; j < wcslen(s->words); j++)
		{
			wchar_t c = text->sentences[i]->words[j];
			if (wcschr(chars, c) == NULL)
			{
				chars[n] = c;
				n++;
				if (n == capacity - 1)
				{
					capacity += BLOCK_SIZE;
					wchar_t* _chars = chars;
					chars = (wchar_t*)realloc(chars, capacity * sizeof(wchar_t*));
					if (chars == NULL) ThrowError(0, _chars);
				}
			}
		}
	}

	for (size_t i = 0; i < wcslen(chars) - 1; i++) wprintf(L"%lc ", chars[i]);
	wprintf(L"%c\n", chars[wcslen(chars) - 1]);
	free(chars);
}