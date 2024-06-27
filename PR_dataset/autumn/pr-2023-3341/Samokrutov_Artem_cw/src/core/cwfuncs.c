#include <stdlib.h>
#include <wchar.h>

#include "cwerror.h"
#include "cwio.h"
#include "cwfuncs.h"
#include "cwprocessing.h"
#include "cwstructures.h"


Text *preprocess_Text(void)
{	
	Text *text = (Text *)calloc(1, sizeof(Text));

	if (text == NULL)
		throw_error(MEMORY_ERR_MSG);

	wchar_t *input = read(&(text->len));

        string_to_proper_Text(text, input);

	free(input);

        fill_len(text);
	fill_first_word_len(text);	

	return text;
}

int count_words(Sentence sentence) 
{
	wchar_t *characters_copy = (wchar_t *)malloc((sentence.len + 1) * sizeof(wchar_t));

	if (characters_copy == NULL)
		throw_error(MEMORY_ERR_MSG);

	wcscpy(characters_copy, sentence.characters);

	int count = 0;
	wchar_t *buf;
	wchar_t *token = wcstok(characters_copy, WORD_SEPARATORS, &buf);
	while (token != NULL) {
		count += 1;
		token = wcstok(NULL, WORD_SEPARATORS, &buf);
	}
	
	free(characters_copy);
	return count;
}

int max_word_len(Sentence sentence)
{
	wchar_t *characters_copy = (wchar_t *)malloc((sentence.len + 1) * sizeof(wchar_t));
	
	if (characters_copy == NULL)
		throw_error(MEMORY_ERR_MSG);

	wcscpy(characters_copy, sentence.characters);

	int max_len = 0;
	wchar_t *buf;
	wchar_t *token = wcstok(characters_copy, WORD_SEPARATORS, &buf);
	while (token != NULL) {
		max_len = wcslen(token) > max_len ? wcslen(token) : max_len;
		token = wcstok(NULL, WORD_SEPARATORS, &buf);
	}
	
	free(characters_copy);
	return max_len;
}

void date(Sentence sentence)
{	
	int day = count_words(sentence);
	int month = max_word_len(sentence);
	int year = YEAR_OFFSET + sentence.len;

	wprintf(L"%ls: %i-%i-%i\n", sentence.characters, day, month, year);
}

void dateify(Text *text)
{
	for (int i = 0; i < text->len; i++){
		date(text->sentences[i]);
	}
}

void reverse_part(wchar_t *str, int start, int end)
{
	for (int i = 0; i < (end - start) / 2; i++) {
		wchar_t tmp = str[start + i];
		str[start + i] = str[end - i - 1];
		str[end - i - 1] = tmp;
	}
}

void reverse_each_word(wchar_t *str) 
{
	wchar_t *tmp = (wchar_t *)calloc(wcslen(str) + 1, sizeof(wchar_t));

	if (tmp == NULL)
		throw_error(MEMORY_ERR_MSG);

	wcscpy(tmp, str);

	wchar_t *buf;
	wchar_t *token = wcstok(tmp, WORD_SEPARATORS, &buf);

	if (token != NULL)
		reverse_part(str, 0, token - tmp);

	while (token != NULL) {
		reverse_part(str, token - tmp, token - tmp + wcslen(token));
	
		int offset = (token - tmp) + wcslen(token);
		token = wcstok(NULL, WORD_SEPARATORS, &buf);
		if (token != NULL)
			reverse_part(str, offset, token - tmp);
		else
			reverse_part(str, offset, wcslen(str));
	}

	free(tmp);
}

void reverse_word_order(wchar_t *str)
{
	reverse_each_word(str);

	reverse_part(str, 0, wcslen(str));
}

void reverse_Text(Text *text)
{
	for (int i = 0; i < text->len; i++) {
		reverse_word_order(text->sentences[i].characters);
	}
}

int first_word_len_cmp(const void *a, const void *b)
{
	Sentence sentence_a = *(Sentence *)a;
	Sentence sentence_b = *(Sentence *)b;

	int len_a = sentence_a.first_word_len;
	int len_b = sentence_b.first_word_len;

	return (len_a >= len_b) - (len_a <= len_b);
}

void sort_by_first_word_len(Text *text)
{
	qsort(text->sentences, text->len, sizeof(Sentence), first_word_len_cmp);

}


int words_are_too_short(Sentence sentence)
{
	wchar_t *characters = (wchar_t *)malloc((sentence.len + 1) * sizeof(wchar_t));

	if (characters == NULL)
		throw_error(MEMORY_ERR_MSG);

	wcscpy(characters, sentence.characters);
	
	wchar_t *buf;
	wchar_t *word = wcstok(characters, WORD_SEPARATORS, &buf);
	while (word != NULL) {
		if (wcslen(word) >= MIN_ALLOWED_WORD_LEN) {
			free(characters);
			return 0;
		}
		
		word = wcstok(NULL, WORD_SEPARATORS, &buf);
	}
	
	free(characters);
	return 1;
}

void print_Sentences_with_short_words(Text *text)
{
	for (int i = 0; i < text->len; i++) {
		if (!words_are_too_short(text->sentences[i])) {
			wprintf(L"%ls.\n", text->sentences[i].characters);
		}
	}
}	

int is_palindrome(wchar_t *line)
{
	int i = 0, j = wcslen(line) - 1;
	while (i < j && i < wcslen(line) && j > 0) {
		if (!iswalnum(line[i])) {
			i++;
			continue;
		}
		if (!iswalnum(line[j])) {
			j--;
			continue;
		}

		if (towupper(line[i]) != towupper(line[j])) {
			return 0;
		} else {
			i++;
			j--;
		}
	}

	return 1;
}

void print_palindromes(Text *text)
{
	for (int i = 0; i < text->len; i++) {
		if (is_palindrome(text->sentences[i].characters)) {
			wprintf(L"%ls.\n", text->sentences[i].characters);
		}
	}
}



void task_match(Text *text, int task)
{
	switch(task) {
	case 0:
		text = preprocess_Text();
		print_Text(text);
		free_Text(text);
		break;
	case 1:
		text = preprocess_Text();
		dateify(text);
		free_Text(text);
		break;
	case 2:
		text = preprocess_Text();
		reverse_Text(text);
		print_Text(text);
		free_Text(text);
		break;
	case 3:
		text = preprocess_Text();
		sort_by_first_word_len(text);
		print_Text(text);
		free_Text(text);
		break;
	case 4:
		text = preprocess_Text();
		print_Sentences_with_short_words(text);
		free_Text(text);
		break;
	case 5:
		help();
		break;
	case 8:
		text = preprocess_Text();
		print_palindromes(text);
		free_Text(text);
		break;
	default:
		throw_error(TASK_ERR_MSG);
	}
}
