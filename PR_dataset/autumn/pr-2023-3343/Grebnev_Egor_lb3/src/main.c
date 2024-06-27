#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MEMORY_CHUNK 20;
char** split_text(char* text, int* num_sentences, const char* spliters);
void remove_lead_spaces(char* str);
int remove_sentences_with_uppercases(char** splitted_text, int current_num_sentence);
char* get_text_input(const char* end_symbol);

int main(void) {
	int num_sentences = 0;
	const char* spliters = ".;?";
	const char* end_symbol = "!";
	char* text = get_text_input(end_symbol);
	char** splitted_text = split_text(text, &num_sentences, spliters);

	
	int result_num_sentences = remove_sentences_with_uppercases(splitted_text, num_sentences);

	for (int i = 0; i < result_num_sentences; i++) {
		printf("%s\n", splitted_text[i]);
		free(splitted_text[i]);
	}
	printf("Количество предложений до %d и количество предложений после %d\n", num_sentences - 1, result_num_sentences - 1);
	free(splitted_text);
	free(text);
	return 0;
}


char* get_text_input(const char* end_symbol) {
    unsigned int size = 0, capacity = MEMORY_CHUNK;
    char ch;
    char* text = malloc(sizeof(char*));
    while ((ch = getchar()) != *end_symbol) {
        if (ch != '\n') {
			if (size >= capacity - 1){
				capacity += MEMORY_CHUNK;
				text = realloc(text, capacity * sizeof(char));
			}
            text[size++] = ch;
        }
    }
	text = realloc(text, (size + 2) * sizeof(char));
	text[size++] = *end_symbol;
	text[size] = '\0'; 
    return text;
}


char** split_text(char* text, int* num_sentences, const char* spliters) {
	int count_sentences = 0;
	int end_index = 0;
	char** splitted_text = malloc(sizeof(char*));

	for (int i = 0; i <= (int)strlen(text); i++) {
		if (strchr(spliters, text[i]) != NULL) {
			count_sentences++;

			splitted_text = realloc(splitted_text, count_sentences * sizeof(char*));
			splitted_text[count_sentences - 1] = malloc((end_index + 2) * sizeof(char));

			int chr_counter = 0;
			for (int j = end_index; j >= 0; j--) {
				splitted_text[count_sentences - 1][chr_counter++] = text[i - j];
			}
			splitted_text[count_sentences - 1][chr_counter] = '\0';
			remove_lead_spaces(splitted_text[count_sentences - 1]);
			end_index = 0;
			continue;
		}
		end_index++;
	}

	*num_sentences = count_sentences;
	return splitted_text;
}

void remove_lead_spaces(char* str) {
	char* start = str;

	while (*start && (*start == ' ' || *start == '\t' ||  *start == '\n')) {
		start++;
	}

	memmove(str, start, strlen(start) + 1);
}

int remove_sentences_with_uppercases(char** splitted_text, int current_num_sentence) {
	int sentence_counter = 0;
	for (int i = 0; i < current_num_sentence; ++i) {
		int uppercaseCount = 0;
		char* sentence = splitted_text[i];

		for (int j = 0; j < (int)strlen(sentence); ++j) {
			if (isupper(sentence[j])) {
				uppercaseCount++;
			}
		}
		if (uppercaseCount <= 1) {
			splitted_text[sentence_counter] = strdup(sentence);
			sentence_counter++;
		}
	}


	return sentence_counter;
}

