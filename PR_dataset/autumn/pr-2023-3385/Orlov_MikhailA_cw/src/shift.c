#include "shift.h"
#include "textio.h"
#include "errors.h"

#define BLOCK_SIZE (size_t)32

void ShiftWords(const Text* text, size_t n, int N)
{
	size_t capacity = BLOCK_SIZE;
	wchar_t** words = (wchar_t**)malloc(BLOCK_SIZE * sizeof(wchar_t*));
	size_t k = 0;
	for (; text->sentences[n]->words != NULL && text->sentences[n]->words[0] != L'\000'; k++)
	{
		words[k] = wcstok(text->sentences[n]->words, L" ", &text->sentences[n]->words);
		if (k == capacity - 1)
		{
			capacity += BLOCK_SIZE;
			wchar_t** _words = words;
			words = (wchar_t**)realloc(words, capacity * sizeof(wchar_t*));
			if (words == NULL) ThrowError(0, _words);
		}
	}
	N %= k;
	for (size_t i = 0, j = N; j < k + N; i++, j++)
	{
		wprintf(words[j % k]);
		wprintf(L" ");
	}
	wprintf(L".\n");
	for (size_t i = 0; i < k; i++) free(words[i]);
	free(words);
}

void ShiftText(const Text* text, int N)
{
	if (!N)
	{
		PrintText(text);
		return;
	}
	for (size_t i = 0; i < text->count; i++) ShiftWords(text, i, N);
}