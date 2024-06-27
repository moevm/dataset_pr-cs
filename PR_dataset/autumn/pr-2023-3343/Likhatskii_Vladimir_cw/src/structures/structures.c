#include "structures.h"

void Text_push(Text *text, wchar_t * sentence_text) {
    text->sentences = realloc(text->sentences, (text->length + 1) * sizeof(Sentence));
    text->sentences[text->length].text = sentence_text;
    text->length++;
}

Text *Text_from_string(wchar_t *str) {
    int end_index = 0, chr_counter = 0;
	Text *text = malloc(sizeof(Text));
	text->length = 0;
	text->sentences = (Sentence *)malloc(sizeof(Sentence));
	
	for (size_t i = 0; i < wcslen(str); i++)
	{
		if (wcschr(SENTENCE_END, str[i]) != NULL)
		{
            wchar_t *sentence = malloc((long unsigned)(end_index + 2) * sizeof(wchar_t));

			chr_counter = 0;

			for (int j = end_index; j >= 0; j--)
				sentence[chr_counter++] = str[i - j];

			sentence[chr_counter] = L'\0';
			sentence = trimstart(sentence, TEXT_DELIMITERS);
			end_index = 0;
            if(!isempty(sentence)) {
                Text_push(text, sentence);
            }
			continue;
		}
		end_index++;
	}
	return text;
}
