#include <stdlib.h>
#include <wctype.h>
#include "txtprocessing.h"
#include "input.h"
#include "memory.h"
#include "log.h"

void removeUpperCaseLettersSentence(Sentence *sentence)
{
	wchar_t *input = sentence->sentence;
	int j = 0;
	for (int i = 0; input[i] != L'\0'; ++i)
	{
		if (!iswupper((wint_t)input[i]))
			input[j++] = input[i];
	}
	input[j] = L'\0';
}

void removeUpperCaseLettersText(Text *text)
{
	for (unsigned int i = 0; i < text->num_sentences; ++i)
		removeUpperCaseLettersSentence(&(text->sentences[i]));
}

void removeRepeats(Text *text)
{
	unsigned int newSize = text->num_sentences;
	for (unsigned int i = 0; i < newSize; ++i)
	{
		for (unsigned int j = i + 1; j < newSize; ++j)
		{
			if (wcscasecmp(text->sentences[i].sentence, text->sentences[j].sentence) == 0)
			{
				free(text->sentences[j].sentence);
				for (unsigned int k = j; k < newSize - 1; ++k)
				{
					text->sentences[k] = text->sentences[k + 1];
				}
				--newSize;
				--j;
			}
		}
	}
	text->num_sentences = newSize;
}

void removeLeadSpaces(wchar_t *str)
{
	wchar_t *start = str;
	while (*start && (iswspace((wint_t)*start) || *start == L'\t'))
		start++;

	wmemmove(str, start, wcslen(start) + 1);
}
Text split_text(const wchar_t *raw_text, const wchar_t *spliters)
{
	int end_index = 0, chr_counter = 0;
	Text text;
	text.num_sentences = 0;
	text.sentences = (Sentence *)malloc(sizeof(Sentence));
	checkMemoryAllocation(text.sentences, L"Insufficient memory for text structure");

	for (size_t i = 0; i < wcslen(raw_text); i++)
	{
		if (wcschr(spliters, raw_text[i]) != NULL)
		{
			text.num_sentences++;

			text.sentences = (Sentence *)realloc(text.sentences, text.num_sentences * sizeof(Sentence));
			text.sentences[text.num_sentences - 1].sentence = (wchar_t *)malloc((long unsigned)(end_index + 2) * sizeof(wchar_t));
			checkMemoryAllocation(text.sentences[text.num_sentences - 1].sentence, L"Insufficient memory for text structure");

			chr_counter = 0;

			for (int j = end_index; j >= 0; j--)
				text.sentences[text.num_sentences - 1].sentence[chr_counter++] = raw_text[i - (size_t)j];

			text.sentences[text.num_sentences - 1].sentence[chr_counter] = L'\0';
			removeLeadSpaces(text.sentences[text.num_sentences - 1].sentence);

			end_index = 0;
			continue;
		}
		end_index++;
	}
	return text;
}

Text *createTextStruct(const wchar_t *spliters)
{
	Text *text = (Text *)malloc(sizeof(Text));
	checkMemoryAllocation(text, L"Insufficient memory for text structure");
	wchar_t *raw_text = getTextInput();
	*text = split_text(raw_text, spliters);
	removeRepeats(text);
	free(raw_text);
	return text;
}

void removeWithoutSpecialChars(Text *text)
{
	unsigned int validSentenceCount = 0;
	for (unsigned int i = 0; i < text->num_sentences; ++i)
	{
		wchar_t *sentence = text->sentences[i].sentence;
		int hasSpecialChars = 0;
		for (size_t j = 0; !hasSpecialChars && sentence[j + 1] != L'\0'; ++j)
			hasSpecialChars = !iswalnum((wint_t)sentence[j]) && !iswspace((wint_t)sentence[j]);

		if (hasSpecialChars)
			text->sentences[validSentenceCount++] = text->sentences[i];
		else
			free(text->sentences[i].sentence);
	}

	text->num_sentences = validSentenceCount;
	text->sentences = (Sentence *)realloc(text->sentences, sizeof(Sentence) * validSentenceCount);
	checkMemoryAllocation(text->sentences, L"Memory override error for text structure");
}

wchar_t *concat(const wchar_t *s1, const wchar_t *s2)
{
    wchar_t *result = malloc((wcslen(s1) + wcslen(s2) + 3) * sizeof(wchar_t));
    wcscpy(result, s1);
    wcscat(result, L" ");
    wcscat(result, s2);
    wcscat(result, L" ");
    return result;
}

void duplicateWords(Text *text)
{
    for (size_t i = 0; i < text->num_sentences; i++)
    {
        wchar_t *sentence = text->sentences[i].sentence;
        wchar_t *newSentence = malloc((wcslen(sentence) + 1) * sizeof(wchar_t) * 2);

        wchar_t *tokBuffer;
        wchar_t *word;

        newSentence[0] = L'\0';

        for (word = wcstok(sentence, L" ,.", &tokBuffer); word != NULL; word = wcstok(NULL, L" ,.", &tokBuffer))
        {
            wcscat(newSentence, concat(word, word));
        }

        size_t len = wcslen(newSentence);
        newSentence[len - 1] = L'.';
        newSentence[len] = L'\0';

        text->sentences[i].sentence = realloc(text->sentences[i].sentence, (len + 1) * sizeof(wchar_t));
        wcscpy(text->sentences[i].sentence, newSentence);

        free(newSentence);
    }
}