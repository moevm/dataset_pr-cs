#include "uppercase.h"
#include "textio.h"
#include "errors.h"
#include <wctype.h>
#include <stdint.h>

#define BLOCK_SIZE (size_t)32

void RemoveLastUppercaseWords(const Text* text)
{
	wchar_t** words;
	size_t capacity = BLOCK_SIZE;

	for (size_t i = 0; i < text->count; i++)
	{
		words = (wchar_t**)malloc(BLOCK_SIZE * sizeof(wchar_t*));
		for (size_t k = 0; text->sentences[i]->words != NULL && text->sentences[i]->words[0] != L'\000'; k++)
		{
			words[k] = wcstok(text->sentences[i]->words, L" ", &text->sentences[i]->words);
			if (k == capacity - 1)
			{
				capacity += BLOCK_SIZE;
				wchar_t** _words = words;
				words = (wchar_t**)realloc(words, capacity * sizeof(wchar_t*));
				if (words == NULL) ThrowError(0, _words);
			}
			if (!iswupper(words[k][wcslen(words[k]) - 1])) wprintf(L"%ls ", words[k]);
		}
		wprintf(L".\n");
		free(words);
	}
}