#include <stdlib.h>
#include <wchar.h>

#include "cwerror.h"
#include "cwio.h"
#include "cwstructures.h"


void fill_len(Text *text)
{
	for (int i =0; i < text->len; i++) {
		text->sentences[i].len = wcslen(text->sentences[i].characters);
	}
}

void fill_first_word_len(Text *text)
{
	for (int i = 0; i < text->len; i++) {
		wchar_t *characters_copy = (wchar_t *)malloc((text->sentences[i].len + 1) * sizeof(wchar_t));

		if (characters_copy == NULL)
			throw_error(MEMORY_ERR_MSG);

		wcscpy(characters_copy, text->sentences[i].characters);

		wchar_t *delim = WORD_SEPARATORS;
		wchar_t *buf;
		wchar_t *token = wcstok(characters_copy, delim, &buf);

                if (token != NULL)
			text->sentences[i].first_word_len = wcslen(token);
		else 
			text->sentences[i].first_word_len = 0;

		free(characters_copy);
	}
}

void Sentence_cpy(Sentence *dst, Sentence *src)
{
	wcscpy(dst->characters, src->characters);
	dst->len = src->len;
	dst->first_word_len = src->first_word_len;
}

void delete_Sentence(Text *text, int n)
{
	for (int i = n; i < text->len - 1; i++) {
		Sentence_cpy(&(text->sentences[i]), &(text->sentences[i + 1]));
	}

	free(text->sentences[text->len].characters);
	(text->len)--;
}

void free_Text(Text *text)
{
	for (int i = 0; i < text->len; i++)
		free(text->sentences[i].characters);

	free(text->sentences);
	free(text);
}

