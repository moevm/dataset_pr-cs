#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define START_SIZE 20
#define PLUS_SIZE 15
#define MEMORY_ERROR "Error: ошибка выделения памяти.\n"

char** input(int*);
void output(char**, int*);
void plus_text_memory(char***, int*);
void plus_sentence_memory(char**, int*);
void free_text_memory(char**, int*);
char** delete_sentence(char**, int, int);
char** delete_repeated_sentences(char**, int*);
char** delete_empty_sentences(char**, int*);
char* duplicate(char*, int, int);
char* find_word_to_delete(char*);
char** f1_delete_entered_word(char** text, int* size_of_text);
int cmp_chars(const void*, const void*);
void f2_print_upper_letters_for_sentences(char**, int*);
int cmp_numbers(const void*, const void*);
float count_average(char*);
char** f3_sort_text_by_averages(char**, int*);
char** f4_delete_sentences_without_lower_letters(char**, int*);
void f5_menu();
void f9(char**, int*);
void binary(char*);

int main() {
	printf("Course work for option 4.20, created by Mariya Kunakova.\n");
	char command;
	command = getchar();
	if ((command != '0') && (command != '9') && (command != '1') && (command != '2') && (command != '3') && (command != '4') && (command != '5')) {
		printf("Error: введена неверная команда.\n");
		exit(0);
	}
	else {
		if (command == '0') {
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			output(real_text, &size_of_text);
			free_text_memory(real_text, &size_of_text);
			exit(0);
		}
		if (command == '1') {
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			real_text = f1_delete_entered_word(real_text, &size_of_text);
			output(real_text, &size_of_text);
			free_text_memory(real_text, &size_of_text);
			exit(0);
		}
		if (command == '2') {
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			f2_print_upper_letters_for_sentences(real_text, &size_of_text);
			free_text_memory(real_text, &size_of_text);
			exit(0);
		}
		if (command == '3') {
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			real_text = f3_sort_text_by_averages(real_text, &size_of_text);
			output(real_text, &size_of_text);
			free_text_memory(real_text, &size_of_text);
			exit(0);
		}
		if (command == '4') {
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			real_text = f4_delete_sentences_without_lower_letters(real_text, &size_of_text);
			output(real_text, &size_of_text);
			free_text_memory(real_text, &size_of_text);
			exit(0);
		}
		if (command == '5') {
			f5_menu();
			exit(0);
		}
		if(command == '9')
		{
			int size_of_text = 0;
			char** real_text = input(&size_of_text);
			real_text = delete_repeated_sentences(real_text, &size_of_text);
			f9(real_text, &size_of_text);
			exit(0);
		}	
	}
}

char** input(int* size) {
	int real_text_size = START_SIZE;
	char** text = malloc(sizeof(char*) * real_text_size);
	int sentence = 0;
	int symbol = 0;
	int counter_enters = 0;
	int real_sentence_size = START_SIZE;
	char current_symbol;
	do {
		current_symbol = getchar();
		if (symbol >= real_sentence_size) {
			plus_sentence_memory(&text[sentence], &real_sentence_size);
		}
		if (sentence >= real_text_size) {
			plus_text_memory(&text, &real_text_size);
		}
		if (symbol == 0) {
			text[sentence] = calloc(real_sentence_size, sizeof(char));
		}
		if (current_symbol == '.') {
			if(symbol == 0){
				continue;
			}
			text[sentence][symbol] = '\0';
			sentence++;
			symbol = 0;
			continue;
		}
		if (isspace(current_symbol) && symbol == 0 && current_symbol != '\n') {
			continue;
		}
		if (isalpha(current_symbol) || isdigit(current_symbol) || isspace(current_symbol) || current_symbol == ',') {
			if (current_symbol == '\n') {
				counter_enters++;
				if (counter_enters > 0) {
					if (counter_enters == 2) {
						text[sentence][symbol - 1] = '\0';
						if (symbol != 0) {
							sentence++;
						}
						break;
					}
					else {
						if (symbol == 0) {
							continue;
						}
						text[sentence][symbol] = current_symbol;
						symbol++;
						continue;
					}
				}
			}
			else {
				counter_enters = 0;
				text[sentence][symbol] = current_symbol;
				symbol++;
				continue;
			}
		}
		else {
			printf("Error: неверный формат ввода.\n");
			free_text_memory(text, &sentence);
			exit(0);
		}
	} while (1);
	*size = sentence;
	return text;
}

void output(char** text, int* size_of_text) {
	for (int i = 0; i < *size_of_text; i++) {
		printf("%s.\n", text[i]);
	}
}

void plus_text_memory(char*** text, int* size_of_text) {
	char** test_text_memory = (char**)realloc(*text, (*size_of_text + PLUS_SIZE) * sizeof(char*));
	if (test_text_memory != NULL) {
		*text = test_text_memory;
		*size_of_text += PLUS_SIZE;
	}
	else {
		printf(MEMORY_ERROR);
		exit(0);
	}
}

void plus_sentence_memory(char** sentence, int* size_of_sentence) {
	char* test_sentence_memory = (char*)realloc(*sentence, (*size_of_sentence + PLUS_SIZE) * sizeof(char));
	if (test_sentence_memory != NULL) {
		*sentence = test_sentence_memory;
		*size_of_sentence += PLUS_SIZE;
	}
	else {
		printf(MEMORY_ERROR);
		exit(0);
	}
}

void free_text_memory(char** text, int* size_of_text) {
	int size = *size_of_text;
	for (int i = 0; i < size; i++) {
		free(text[i]);
	}
	free(text);
}

char** delete_sentence(char** text, int size_of_text, int index_to_delete) {
	for (int i = index_to_delete; i < size_of_text; i++) {
		text[i] = text[i + 1];
	}
	return text;
}

char** delete_repeated_sentences(char** text, int* size_of_text) {
	int size_after = *size_of_text;
	for (int i = 0; i < *size_of_text; i++) {
		for (int j = 0; j < i; j++) {
			if(strlen(text[i]) == strlen(text[j])){
                int flag = 0;
                for(int k = 0; k < strlen(text[i]); k++){
                    if(tolower(text[i][k]) != tolower(text[j][k])){
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0) {
                    text = delete_sentence(text, size_after, i);
                    i--;
                    size_after--;
                    *size_of_text = size_after;
                }
            }
		}
	}
	return text;
}

char** delete_empty_sentences(char** text, int* size_of_text) {
	int size_after = *size_of_text;
	for (int i = 0; i < *size_of_text; i++) {
		int size_of_sentence = strlen(text[i]);
		int flag = 0;
		for (int j = 0; j < size_of_sentence; j++) {
			if (isalnum(text[i][j])) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			text = delete_sentence(text, size_after, i);
			i--;
			size_after--;
			*size_of_text = size_after;
		}
	}
	return text;
}

char* duplicate(char* sentence, int start_index, int end_index) {
	int len_word = end_index - start_index;
	char* duplicate = (char*)malloc(sizeof(char) * (len_word + 1));
	if (duplicate != NULL) {
		for (int i = 0; i < len_word; i++) {
			duplicate[i] = sentence[start_index + i];
		}
		duplicate[len_word] = '\0';
	}
	else {
		printf(MEMORY_ERROR);
		exit(0);
	}
	return duplicate;
}

char* find_word_to_delete(char* sentence) {
	int end_index_of_word = 0;
	while (isalnum(sentence[end_index_of_word])) {
		end_index_of_word++;
	}
	char* word = duplicate(sentence, 0, end_index_of_word);
	return word;
}

char** f1_delete_entered_word(char** text, int* size_of_text) {
    char* word_to_delete = find_word_to_delete(text[0]);
    for (int i = 0; i < *size_of_text; i++) {
        int word_start = 0;
        int word_end = 0;
        int len_of_sent = strlen(text[i]);
        while (word_start < len_of_sent) {
            while (word_start < len_of_sent && !(isalnum(text[i][word_start]))) {
                word_start++;
            }
            word_end = word_start;
            while (word_end < len_of_sent && isalnum(text[i][word_end])) {
                word_end++;
            }
            if (word_end > word_start) {
                char* current_word = duplicate(text[i], word_start, word_end);
                if (strlen(current_word) == strlen(word_to_delete)){
                    int flag = 0;
                    for(int j = 0; j < strlen(current_word); j++){
                        if(tolower(current_word[j]) != tolower(word_to_delete[j])){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0){
                        if (word_end < len_of_sent && isspace(text[i][word_end])) {
                            memmove(&text[i][word_start], &text[i][word_end + 1], len_of_sent - word_end);
                            len_of_sent -= (word_end - word_start + 1);
                        } else if (word_start > 0 && isspace(text[i][word_start - 1])) {
                            memmove(&text[i][word_start - 1], &text[i][word_end], len_of_sent - word_end + 1);
                            len_of_sent -= (word_end - word_start + 1);
                            word_start--;
                        } else {
                            memmove(&text[i][word_start], &text[i][word_end], len_of_sent - word_end + 1);
                            len_of_sent -= (word_end - word_start);
                            word_start--;
                        }
                    }
                }
                free(current_word);
            }
            word_start = word_end;
        }
    }
    text = delete_empty_sentences(text, size_of_text);
    return text;
}

int cmp_chars(const void* a, const void* b) {
	return (*(char*)a - *(char*)b);
}

void f2_print_upper_letters_for_sentences(char** text, int* size_of_text) {
	for (int j = 0; j < *size_of_text; j++) {
		int size_of_sentence = strlen(text[j]);
		char upper_letters[size_of_sentence];
		int counter_letters = 0;
		for (int i = 0; i < strlen(text[j]); i++) {
			if (isupper(text[j][i])) {
				upper_letters[counter_letters] = text[j][i];
				counter_letters++;
			}
		}
		if (counter_letters == 0) {
			continue;
		}
		qsort(upper_letters, counter_letters, sizeof(char), cmp_chars);
		for (int i = 0; i < counter_letters; i++) {
			printf("%c", upper_letters[i]);
		}
		printf("\n");
	}
}

int cmp_numbers(const void* a, const void* b) {
	char* s1 = *((char**)a);
	char* s2 = *((char**)b);
	float average_s1 = count_average(s1);
	float average_s2 = count_average(s2);
	return (average_s2 > average_s1);
}

float count_average(char* sentence) {
	int sum = 0;
	int count_numbers = 0;
	char* copy_sentence = duplicate(sentence, 0, strlen(sentence) - 1);
	char* word = strtok(copy_sentence, " ,.\t\n");
	while (word != NULL) {
		int flag = 0;
		for (int i = 0; i < strlen(word); i++) {
			if (!(isdigit(word[i]))) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			sum += atoi(word);
			count_numbers++;
		}
		word = strtok(NULL, " ,.\t\n");
	}
	if (count_numbers == 0) {
		return 0;
	}
    float res = sum / count_numbers;
	return res;
}

char** f3_sort_text_by_averages(char** text, int* size_of_text) {
	qsort((void*)text, *size_of_text, sizeof(char*), cmp_numbers);
	return text;
}

char** f4_delete_sentences_without_lower_letters(char** text, int* size_of_text) {
	int size_after = *size_of_text;
	for (int i = 0; i < *size_of_text; i++) {
		int flag = 0;
		for (int j = 0; j < strlen(text[i]); j++) {
			if (islower(text[i][j])) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			text = delete_sentence(text, size_after, i);
			i--;
			size_after--;
			*size_of_text = size_after;
		}
	}
	return text;
}

void f5_menu() {
	printf("0 - вывод текста после первичной обязательной обработки - удаления повторно встречающихся предложений\n1 - удалить слово, введённое пользователем\n2 - для каждого предложения вывести все заглавные буквы в лексикографическом порядке\n3 - отсортировать предложения по среднему арифметическому чисел в предложении\n4 - удалить все предложения, в которых нет строчных букв\n5 - вывод справки о функциях, которые реализует программа\n");
}



void f9(char** text, int* size_of_text){
	for(int i = 0; i < *size_of_text; i++){
		char* sentence = text[i];
		for(int j = 0; j < strlen(sentence); j++){
			if(isalpha(sentence[j]) || isspace(sentence[j])){
				printf("%c", sentence[j]);
			}
			else{
				if(isdigit(sentence[j])){
					char* digit = malloc(sizeof(char)*strlen(sentence));
					digit[0] = sentence[j];
					int count = 1;
					for(int k =j + 1; k < strlen(sentence); k++){
						if(isdigit(sentence[k])){
							digit[count] =sentence[k];
							count++;
						}
						else{
							digit[count] = '\0';
							break;
						}
					}
					binary(digit);
					j += count - 1;
					free(digit);
					//func to do perevod v 2 system	
				}		
			}
		}
		printf(".\n");	
	}		
}
void binary(char* dig){
        int i = 0;
        int dex = atoi(dig);
        char r[100];
        while(dex != 0){
                if(dex % 2 == 0){
                        r[i] = '0';
                        dex = dex / 2;
                }
                else{
                        r[i] = '1';
                        dex = dex / 2;
                }
                i++;
        }
        r[i] = '\0';
        char s[4] = "0b\0";
        printf("%s", s);
        for(int j = strlen(r); j >= 0; j--){
                if(r[j] != '\0'){
                        printf("%c",r[j]);

                }

        }
}

