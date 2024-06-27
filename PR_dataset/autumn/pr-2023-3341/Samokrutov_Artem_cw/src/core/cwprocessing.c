#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

#include "cwerror.h"
#include "cwfuncs.h"
#include "cwio.h"
#include "cwprocessing.h"
#include "cwstructures.h"

int Text_nduplicate(Text *text, wchar_t *string, int count)
{
	for (int i = 0; i < count; i++) {
		if (!wcscasecmp(text->sentences[i].characters, string)) {
			return 1;
		}
	}
	return 0;
}

void trim_start(wchar_t **string)
{
	while (iswspace(**string)) {
		(*string)++;
	}
}

void string_to_proper_Text(Text *text, wchar_t *string)
{
	text->sentences = (Sentence *)calloc(text->len, sizeof(Sentence));

	if (text->sentences == NULL)
		throw_error(MEMORY_ERR_MSG);

	int curr = 0;
	wchar_t *delim = SENTENCE_SEPARATORS;
	wchar_t *buf;
	wchar_t *token = wcstok(string, delim, &buf);
	while (token != NULL && !wcsstr(token, TERMINATION_SEQUENCE)) {
		trim_start(&token);

		if (!Text_nduplicate(text, token, curr) && wcslen(token) > 0) {
			int token_len = wcslen(token);
			text->sentences[curr].characters = (wchar_t *)calloc(token_len + 1, sizeof(wchar_t));

			if (text->sentences[curr].characters == NULL)
				throw_error(MEMORY_ERR_MSG);

			wcscpy(text->sentences[curr].characters, token);
			text->sentences[curr].characters[token_len] = STRING_TERMINATOR;

			curr++;
		}
		token = wcstok(NULL, delim, &buf);
	}

	if (curr == 0)
		throw_error(NO_WORDS_ERR_MSG);

	text->len = curr;
}
