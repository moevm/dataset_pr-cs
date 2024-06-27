#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 100
#define PLUS_SIZE 20
#define STOP_SENTENCE "Dragon flew away!"

int last_symbol_of_text(char* text) {
	int len_of_text = strlen(text);
	if (text[len_of_text - 1] == '?') {
		return 1;
	}
	return 0;
}

int main() {
	int sentences_before = 0, sentences_after = 0, index = 0;
	char current_symbol = ' ';
	int real_text_size = TEXT_SIZE;
	char* text = malloc(sizeof(char) * TEXT_SIZE);
	while (strcmp(text, STOP_SENTENCE)) {
		current_symbol = getchar();
		if (index + 1 >= real_text_size) {
			char* test_text = (char*)realloc(text, sizeof(char) * (real_text_size + PLUS_SIZE));
			if (test_text != NULL) {
				text = test_text;
				real_text_size += PLUS_SIZE;
			}
		}
		if ((index == 0) && (current_symbol == ' ' || current_symbol == '\t')) {
			continue;
		}
		text[index] = current_symbol;
		index++;

		if (text[index - 1] == '.' || text[index - 1] == ';') {
			text[index] = '\0';
			printf("%s\n", text);
			sentences_after++;
			sentences_before++;
			free(text);
			text = (char*)calloc(real_text_size, sizeof(char));
			index = 0;
		}
		if (last_symbol_of_text(text)) {
			sentences_before++;
			free(text);
			text = (char*)calloc(real_text_size, sizeof(char));
			index = 0;
		}
	}
	text[index] = '\0';
	printf("%s\n", text);
	printf("Количество предложений до %d и количество предложений после %d", sentences_before, sentences_after);
	return 0;
}