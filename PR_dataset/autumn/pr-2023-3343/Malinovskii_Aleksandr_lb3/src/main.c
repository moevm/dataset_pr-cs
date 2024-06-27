#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#define BLOCK_SIZE 100

char* get_input(char* last_symbol, int* input_sentences_number);

char** split_text_by_sentences(char* text, char* splitters,
	int input_sentences_number, int* output_sentences_number);

int main()
{
	setlocale(LC_ALL, "Russian");
	char last_symbol = '!';
	int input_sentences_number = 0;
	int output_sentences_number = 0;
	char* text = get_input(&last_symbol, &input_sentences_number);
	char** splitted_text = split_text_by_sentences(text, "?.;!",
		input_sentences_number,&output_sentences_number);
	
	for (int i = 0; i < output_sentences_number; i++) {
		printf("%s\n", splitted_text[i]);
		free(splitted_text[i]);
	}
	// отнимаем -1 т.к. посчитали консольное предложение
	printf("Количество предложений до %d и количество предложений после %d",
			input_sentences_number,output_sentences_number-1);
	
	free(text);
	free(splitted_text);
	return 0;
}

char* get_input(char* last_symbol, int* input_sentences_number) {
	int length = 0;
	int capacity = BLOCK_SIZE;
	char char_temp = 0;
	char* text = malloc(sizeof(char) * capacity);

	//динамическое выделение памяти под исходный текст
	while ((char_temp = getchar()) != *last_symbol) {
		if ((char_temp != '\n')	&& (char_temp != '\t')){
			if (length >= capacity){
				capacity += BLOCK_SIZE;
				text = realloc(text, capacity * sizeof(char));
			}
			//считаем предложения
			if ((char_temp == '.') || (char_temp == ';') || (char_temp == '?')) {
				(*input_sentences_number)++;
			}
			text[length++] = char_temp;
		}
	}

	text = realloc(text, (length + 2) * sizeof(char));
	text[length++] = *last_symbol;
	text[length] = '\0';

	return text;
}

char** split_text_by_sentences(char* text,char* splitters,
	int input_sentences_number, int* output_sentences_number) {
	
	char** splitted_text = malloc(sizeof(char*));
	int sentences_counter = 0;
	int last_ind=0;
	int is_removing_sentence=0;

	for (int i = 0; i < (int)strlen(text); i++) {
		
		if (text[i] == '7') {
			is_removing_sentence = 1;
		}
		
		if (strchr(splitters, text[i])){	
			//не записываем предложения с цифрой 7
			if (is_removing_sentence == 1) {
				is_removing_sentence = 0;
				last_ind = 0;
				continue;
			}

			sentences_counter++;
			splitted_text = realloc(splitted_text, sentences_counter * sizeof(char*));
			splitted_text[sentences_counter - 1] = malloc((last_ind + 2) * sizeof(char));
	
			int chr_temp=0;
			for (int j = last_ind; j >=0; j--) {
				//пропускаем пробел в начале предложения(если он есть)
				if (j == last_ind && text[i - j] == ' ')
					continue;
				splitted_text[sentences_counter - 1][chr_temp++] = text[i - j];
			}
			splitted_text[sentences_counter - 1][chr_temp] = '\0';
			last_ind = 0;
			continue;
		}
		last_ind++;
	}
	*output_sentences_number = sentences_counter;
	return splitted_text;
}


