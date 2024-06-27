#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BASE_SIZE 8

void trim_sentence_left(char *sentence)
{
	size_t len = strlen(sentence);
	int i = 0;
	while (i < (int)len && isspace(sentence[i])) i++;

	for (size_t j = 0; j + i <= len; j++)
		sentence[j] = sentence[j + i];
}

void trim_sentence_right(char *sentence)
{
	size_t len = strlen(sentence);
	
	int i = len - 1;
	while (i >= 0 && isspace(sentence[i])) i--;
	sentence[i + 1] = '\0';
}

void trim_sentence(char *sentence)
{
	trim_sentence_left(sentence);
	trim_sentence_right(sentence);
}

char **read_text(size_t *out_text_len, size_t *out_text_capacity)
{
	char **text;
	size_t text_len = 0;
	size_t text_capacity = BASE_SIZE;

	char *sentence;
	size_t sentence_len = 0;
	size_t sentence_capacity = BASE_SIZE;

	char c  = '\0';

	sentence = (char*)malloc(sizeof(char) * BASE_SIZE);
	text = (char**)malloc(sizeof(char*) * BASE_SIZE);
	if (sentence == NULL || text == NULL) {
		puts("Error: failed to allocate memory");
		exit(0);
	}

	while (1) {
		if (text_len == text_capacity) {
			text_capacity *= 2;
			text = (char**)realloc(text, sizeof(char*) * text_capacity);
			if (text == NULL) {
				puts("Error: failed to reallocate memory");
				exit(0);
			}
		}

		if (sentence_len + 2 == sentence_capacity) {
			sentence_capacity *= 2;
			sentence = (char*)realloc(sentence, sizeof(char) * sentence_capacity);

			if (sentence == NULL) {
				puts("Error: failed to reallocate memory");
				exit(0);
			}
		}
		
		c = getchar();

		int terminate = (c == EOF || (c == '\n' && sentence[sentence_len - 1] == '\n'));

		if (c == '.' || terminate) {
			sentence[sentence_len] = '\0';
			trim_sentence(sentence);

			if (sentence[0] != '\0') {
				size_t len = strlen(sentence); 
				sentence[len] = '.';
				sentence[len + 1] = '\0';
				
				text[text_len++] = sentence;
			}
			else {
				free(sentence);
			}
			
			sentence_len = 0;
			sentence_capacity = BASE_SIZE;
			sentence = (char*)malloc(sizeof(char) * BASE_SIZE);

			if (sentence == NULL) {
				puts("Error: failed to allocate memory");
				exit(0);
			}
		}
		else sentence[sentence_len++] = c;

		if (terminate)
			break;
	}

	free(sentence);

	*out_text_len = text_len;
	*out_text_capacity = text_capacity;
	return text;
}

void preprocess_text(char **text, size_t *text_len) {
	for (size_t i = 0; i < *text_len; i++) {
		trim_sentence(text[i]);

		size_t len = strlen(text[i]);
		for (size_t j = 0; j < len; j++) {
			if (text[i][j] == '\n')
				text[i][j] = ' ';
		}
	}

	size_t n_removed = 0;
	for (size_t i = 0; i < *text_len; i++) {
		text[i - n_removed] = text[i];

		if (strlen(text[i]) == 0) {
			free(text[i]);
			n_removed++;
		}
	}

	*text_len -= n_removed;
}

void print_text(char **text, size_t text_len)
{
	for (size_t i = 0; i < text_len; i++) {
		puts(text[i]);
	}
}

void free_text(char **text, size_t text_len)
{
	for (size_t i = 0; i < text_len; i++) {
		free(text[i]);
	}
	free(text);
}

void print_help_message()
{
	puts(
		"Enter the option number, then enter the text. Text ends with two line breaks\n"
		"Options:\n"
		"    0. Print preprocessed text;\n"
		"    1. Calculate and print time sum;\n"
		"    2. Remove first word in every sentence, print the result;\n"
		"    3. Remove all sentences with words of the same length, print the result;\n"
		"    4. Sort sentences by the number of lowercase letters in it (descendingly).\n"
		"    5. Print help message.\n"
	);
}

size_t count_lowercase(char *str)
{
	size_t len = strlen(str);
	size_t cnt = 0;
	
	for (size_t i = 0; i < len; i++) {
		cnt += islower(str[i]);
	}

	return cnt;
}

int lowercase_cmp(const void* a, const void *b)
{
	return count_lowercase(*(char**)a) < count_lowercase(*(char**)b);
}

void lowercase_count_sort(char **text, size_t text_len)
{
	qsort(text, text_len, sizeof(char*), lowercase_cmp);
}

char *find_word_start(char *str)
{
	while (*str != '\0' && (isspace(*str) || *str == ',' || *str == '.')) str++;
	return str;
}

char *find_word_end(char *str)
{
	while (!isspace(*str) && *str != ',' && *str != '\0' && *str != '.') str++;
	return str;
}

void remove_sentences_with_words_of_same_size(char **text, size_t *text_len)
{
	size_t n_removed = 0;
	for (size_t i = 0; i < *text_len; i++) {
		text[i - n_removed] = text[i];

		int is_equal = 1;
		char *word = find_word_start(text[i]);
		char *word_end = find_word_end(word);
		size_t first_word_len = (size_t)(word_end - word);

		while (word[0] != '\0') {
			if ((size_t)(word_end - word) != first_word_len) {
				is_equal = 0;
				break;
			}

			word = find_word_start(word_end);
			word_end = find_word_end(word);
		}

		if (is_equal) {
			free(text[i]);
			n_removed++;
		}
	}

	*text_len -= n_removed;
}

void remove_first_word_in_every_sentence(char **text, size_t *text_len)
{
	size_t n_removed = 0;
	
	for (size_t i = 0; i < *text_len; i++) {
		text[i - n_removed] = text[i];

		char *word_end = find_word_end(text[i]);
		char *next_word = find_word_start(word_end);

		memmove(text[i], next_word, strlen(next_word) + 1);
		if (text[i][0] == '.' || text[i][0] == '\0') {
			n_removed++;
			free(text[i]);
		}	
	}

	*text_len -= n_removed;
}

void calculate_text_timesum(char **text, size_t text_len)
{
	for (size_t i = 0; i < text_len; i++) {
		int has_time = 0;
		size_t timesum = 0;

		char *word = find_word_start(text[i]);
		char *end  = find_word_end(word);

		while (word[0] != '\0') {
			size_t num;
			int numlen;
			size_t wordlen = (size_t)(end - word);
		
			if (sscanf(word, "%lu%n", &num, &numlen) == 1) {
				if (wordlen - numlen == 3 && memcmp("sec", word + numlen, 3) == 0) {
					has_time = 1;
					timesum += num;
				}
			}

			word = find_word_start(end);
			end  = find_word_end(word);
		}

		if (has_time) {
			int seconds = (timesum % 60);
			int minutes = (timesum / 60) % 60;
			int hours = timesum / 3600;
			printf("%02d:%02d:%02d\n", hours, minutes, seconds);
		}
	}
}

void print_sentences_with_big_sum(char **text, size_t text_len)
{
	size_t first_sum = 0;
	for (char *ptr = text[0]; *ptr != '\0'; ptr++) {
		char c = *ptr;
		if (isdigit(c))
			first_sum += c - '0';
	}

	for (size_t i = 1; i < text_len; i++) {
		size_t sum = 0;
		
		for (char *ptr = text[i]; *ptr != '\0'; ptr++) {
			char c = *ptr;
			if (isdigit(c))
				sum += c - '0';
		}

		if (sum > first_sum)
			printf("(%d) %s\n", (int)(sum - first_sum), text[i]);
	}
}

void process_option(int option)
{
	char **text;
	size_t text_len;
	size_t text_capacity;

	if (option != 5) {
		text = read_text(&text_len, &text_capacity);
		preprocess_text(text, &text_len);
	}

	switch (option) {
		case 0:
			print_text(text, text_len);
			break;
		case 1:
			calculate_text_timesum(text, text_len);
			break;
		case 2:
			remove_first_word_in_every_sentence(text, &text_len);
			print_text(text, text_len);
			break;
		case 3:
			remove_sentences_with_words_of_same_size(text, &text_len);
			print_text(text, text_len);
			break;
		case 4:
			lowercase_count_sort(text, text_len);
			print_text(text, text_len);
			break;
		case 5:
			print_help_message();
			break;
		case 8:
			print_sentences_with_big_sum(text, text_len);
			break;
		default:
			puts("Error: unknown command");
	}

	if (option != 5) {
		free_text(text, text_len);
	}	
}

int main()
{
	int option;
	puts("Course work for option 4.11, created by Daniil Kulach");

	if (scanf("%d", &option) == 0) { 
		puts("Error: failed to read option");
		return 0;
	}

	process_option(option);
}
