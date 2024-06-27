#include "words.h"
#include "errors.h"
#include <wchar.h>

#define BLOCK_SIZE (size_t)32

void PrintWords(const Text* text)
{
	size_t maxLen = 0;

	size_t* count;
	wchar_t** words = (wchar_t**)malloc(BLOCK_SIZE * sizeof(wchar_t*));
	if (words == NULL) ThrowError(0, words);
	size_t k = 0;
	size_t capacity = BLOCK_SIZE;

	for (size_t i = 0; i < text->count; i++)
	{
		for (; text->sentences[i]->words != NULL && text->sentences[i]->words[0] != L'\000'; k++)
		{
			words[k] = wcstok(text->sentences[i]->words, L" ", &text->sentences[i]->words);
			if (k == capacity - 1)
			{
				capacity += BLOCK_SIZE;
				wchar_t** _words = words;
				words = (wchar_t**)realloc(words, capacity * sizeof(wchar_t*));
				if (_words == NULL) ThrowError(0, _words);
			}
		}
	}

	for (size_t i = 0; i < k; i++)
	{
		size_t len = wcslen(words[i]);
		if (maxLen < len) maxLen = len;
	}

	count = (size_t*)calloc(maxLen, sizeof(size_t));
	if (count == NULL) ThrowError(0, count);

	for (size_t i = 0; i < k; i++)
	{
		count[wcslen(words[i]) - 1]++;
	}

	for (size_t n = 0; n < maxLen; n++)
	{
		if (count[n] > 0)
		{
			wprintf(L"%u: %u (", n + 1, count[n]);
			for (size_t i = 0; i < k; i++)
			{
				wchar_t* word = words[i];
				if (wcslen(word) == n + 1) wprintf(L"%ls ", word);
			}
			wprintf(L")\n");
		}
	}
	free(count);
}