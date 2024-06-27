#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BLOCK_SIZE 10

char* input_text();
char** split(char* string, int* count_sentences);
void print_sentences_with_question(char** string, int* count_sentense);

int main() {
    int count_sentences_before, count_sentences_after;
    char** string = split(input_text(), &count_sentences_before);

    count_sentences_after = count_sentences_before;
    print_sentences_with_question(string, &count_sentences_after);
    printf("Количество предложений до %d и количество предложений после %d\n", count_sentences_before - 1, count_sentences_after - 1);

    free(string);
    return 0;
}


char* input_text() {
    char* string = (char*)malloc(BLOCK_SIZE * sizeof(char*));
    size_t size = 0, capacity = BLOCK_SIZE;

    char c = getchar();
    while(c != '!') {
        if(size >= capacity - 1) {
            capacity += BLOCK_SIZE;
            string = (char*)realloc(string, capacity * sizeof(char));
        }
        if(c != '\n')
            string[size++] = c;
        c = getchar();
    }
    string = (char*)realloc(string, (size + 2) * sizeof(char));
    string[size++] = '!';
    string[size] = '\0';
    return string;
}


char** split(char* string, int* count_sentences) {
	int counter = 0;
	int end_index = 0;
	char** splitted_text = malloc(sizeof(char*));

	for (int i = 0; i <= (int)strlen(string); i++) {
		if (strchr(".;?", string[i]) != NULL) {
			counter++;

			splitted_text = realloc(splitted_text, counter * sizeof(char*));
			splitted_text[counter - 1] = malloc((end_index + 2) * sizeof(char));

			int chr_counter = 0;
			for (int j = end_index; j >= 0; j--) {
				splitted_text[counter - 1][chr_counter++] = string[i - j];
			}
			splitted_text[counter - 1][chr_counter] = '\0';
            char* start = splitted_text[counter - 1]; 
        	while (*start && (*start == ' ' || *start == '\t' ||  *start == '\n')) {
        		start++;
        	}
        	memmove(splitted_text[counter - 1], start, strlen(start) + 1);

			end_index = 0;
			continue;
		}
		end_index++;
	}

	*count_sentences = counter;

	return splitted_text;
}


void print_sentences_with_question(char** string, int* count_sentense) {
    int counter = 0;
    for (int i = 0; i < *count_sentense; i++) {
        if(string[i][strlen(string[i]) - 1] != '?') {
            printf("%s\n", string[i]);
            counter++;
        }
    } 
    *count_sentense = counter;
}
