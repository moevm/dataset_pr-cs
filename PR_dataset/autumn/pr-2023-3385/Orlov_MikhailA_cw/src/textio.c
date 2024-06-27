#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include "structs.h"
#include "errors.h"

#define BLOCK_SIZE (size_t)64
#define TEXT_BLOCK_SIZE (size_t)8

Sentence* ReadSentence(int* end)
{
	Sentence* sentence = (Sentence*)malloc(sizeof(Sentence));
	if (sentence == NULL) ThrowError(0, sentence);
	sentence->words = (wchar_t*)malloc(BLOCK_SIZE * sizeof(wchar_t));
	if (sentence->words == NULL) ThrowError(0, sentence->words);

	sentence->count = 0;
	size_t capacity = BLOCK_SIZE;
	int lines = 0;

	while (lines != 2)
	{
		wchar_t c = getwchar();
		if (!(sentence->count == 0 && iswspace(c))) sentence->words[sentence->count++] = c;

		if (c == L'.') break;

		if (c == L'\n')
		{
			lines++;
			if (lines == 2) break;
		}
		else lines = 0;

		if (sentence->count == capacity - 1)
		{
			capacity += BLOCK_SIZE;
			wchar_t* _words = sentence->words;
			sentence->words = (wchar_t*)realloc(sentence->words, capacity * sizeof(wchar_t));
			if (sentence->words == NULL) ThrowError(0, _words);
		}
	}
	sentence->words[sentence->count] = L'\000';
	if (lines == 2)
	{
		*end = 1;
		if (sentence->count > 2)
		{
			sentence->words[sentence->count - 2] = L'.';
			sentence->words[sentence->count - 1] = L'\0';
		}
	}
	return sentence;
}

Text* ReadText()
{
	int end = 0;
	Text* text = (Text*)malloc(sizeof(Text));
	text->sentences = (Sentence**)malloc(TEXT_BLOCK_SIZE * sizeof(Sentence*));
	if (text->sentences == NULL) ThrowError(0, text->sentences);
	text->count = 0;

	size_t capacity = TEXT_BLOCK_SIZE;

	while (!end)
	{
		Sentence* sentence = ReadSentence(&end);

		if (sentence->count > 1)
		{
			text->sentences[text->count++] = sentence;
		}
		else
		{
			free(sentence->words);
			free(sentence);
		}

		if (text->count == capacity - 1)
		{
			capacity += BLOCK_SIZE;
			Sentence** _text = text->sentences;
			text->sentences = (Sentence**)realloc(text->sentences, capacity * sizeof(Sentence*));
			if (text->sentences == NULL)
			{
				text->sentences = _text;
				ThrowError(0, sentence->words);
			}
		}
	}
	return text;
}

void PrintText(const Text* text)
{
	for (size_t i = 0; i < text->count; i++)
	{
		wprintf(L"%ls\n", text->sentences[i]->words);
	}
}

void DeleteText(Text* text)
{
	for (size_t i = 0; i < text->count; i++)
	{
		free(text->sentences[i]->words);
		free(text->sentences[i]);
	}
	free(text);
}