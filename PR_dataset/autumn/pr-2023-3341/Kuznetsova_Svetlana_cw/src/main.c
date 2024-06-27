#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define AUTHOR_INFO "Course work for option 4.5, created by Kuznetsova Svetlana.\n"
#define RED "\033[0;31m"
#define NONE "\033[0m"
#define END_STR '\n'
#define END_LINE '\0'
#define ZERO 48

char *input(int *quantity) {
	int text_size = 0;
	int capacity = 10;
	int end = 0;
	char *arr_text = (char*)malloc(sizeof(char));
	char ch = getchar();
	while (1) {
		ch = getchar();
		if (ch == END_STR) {
			end++;
			if (end >= 2) {
				break;
			}
		}
		if (isalnum(ch) || isblank(ch) || ch == '.' || ch == ',' || ch == END_STR || ch == END_LINE || ch == '/') {
			arr_text[text_size++] = ch;
		}
		else {
			printf("Error: invalid symbol\n");
			break;
		}
		if (text_size + 1 >= capacity) {
			capacity *= 2;
			arr_text = (char*)realloc(arr_text, capacity * sizeof(char));
		}
		if (ch == '.') {
			(*quantity)++;
			ch = getchar();
			if (ch == END_STR) {
				end = 1;
			}
			else {
				end = 0;
			}
		}
	}
	arr_text[text_size - 1] = END_LINE;
	return arr_text;
}

char** split_text(char* arr_text, int* quantity) {
	const char sep[] = ".";
	char* str;
	char** text = (char**)calloc((*(quantity)+1), sizeof(char*));
	str = strtok(arr_text, sep);
	int i = 0;
	while (str != NULL) {
		text[i] = str;
		i++;
		str = strtok(NULL, sep);
	}
	return text;
}

char* do_low(const char* sentence) {
	int len = strlen(sentence);
	char* copy_sentence = (char*)calloc((len + 1), sizeof(char));
	strcpy(copy_sentence, sentence);
	for (int i = 0; i < len; i++) {
		copy_sentence[i] = tolower(copy_sentence[i]);
	}
	return copy_sentence;
}

char** remove_replays(char** text, int* quantity) {
	int count = 0;
	for (int i = 0; i < *quantity; i++) {
		int replays = 0;
		char* first_sentence = do_low(text[i]);
		for (int j = 0; j < i; j++) {
			char* second_sentence = do_low(text[j]);
			if (strcmp(first_sentence, second_sentence) == 0) {
				replays = 1;
				break;
			}
			free(second_sentence);
		}
		free(first_sentence);
		if (replays == 0) {
			text[count++] = text[i];
		}
	}
	*quantity = count;
	return text;
}

typedef struct {
	int day;
	int month;
	int year;
} Date;

int dates_compare(Date dates) {
	time_t my_time = time(NULL);
	struct tm *now = localtime(&my_time);
	if (dates.year != now->tm_year + 1900) return dates.year > now->tm_year + 1900;
	if (dates.month != now->tm_mon + 1) return dates.month > now->tm_mon + 1;
	return dates.day > now->tm_mday;
}

int number(char lett) {
	return (lett - ZERO);
}

int is_dates(char *sentence) {
	int day, month, year;
	int flag = 0;
	for (int i = 0; i < strlen(sentence); i++) {
		if (isdigit(sentence[i]) && isdigit(sentence[i + 1]) && sentence[i + 2] == '/' && isdigit(sentence[i + 3]) && isdigit(sentence[i + 4]) && sentence[i + 5] == '/' && isdigit(sentence[i + 6]) && isdigit(sentence[i + 7]) && isdigit(sentence[i + 8]) && isdigit(sentence[i + 9])) {
			day = (number(sentence[i])) * 10 + number(sentence[i + 1]);
			month = (number(sentence[i + 3])) * 10 + number(sentence[i + 4]);
			year = (number(sentence[i + 6])) * 1000 + (number(sentence[i + 7])) * 100 + (number(sentence[i + 8])) * 10 + number(sentence[i + 9]);
			if (day > 0 && day <= 31 && month > 0 && month <= 12 && year >= 0) {
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

void func_dates(char *sentence) {
	int day, month, year;
	int compare;
	Date dates;
	for (int i = 0; i < strlen(sentence); i++) {
		if (isdigit(sentence[i]) && isdigit(sentence[i + 1]) && sentence[i + 2] == '/' && isdigit(sentence[i + 3]) && isdigit(sentence[i + 4]) && sentence[i + 5] == '/' && isdigit(sentence[i + 6]) && isdigit(sentence[i + 7]) && isdigit(sentence[i + 8]) && isdigit(sentence[i + 9])) {
			day = (number(sentence[i])) * 10 + number(sentence[i + 1]);
			month = (number(sentence[i + 3])) * 10 + number(sentence[i + 4]);
			year = (number(sentence[i + 6])) * 1000 + (number(sentence[i + 7])) * 100 + (number(sentence[i + 8])) * 10 + number(sentence[i + 9]);
			if (day > 0 && day <= 31 && month > 0 && month <= 12 && year >= 0) {
				dates = (Date) { day, month, year };
				compare = dates_compare(dates);
				if (compare) {
					printf("%s%02d/%02d/%04d%s", RED, day, month, year, NONE);
				}
				else {
					printf("%02d/%02d/%04d", day, month, year);
				}
				i = i + 9;
			}
		}
		else {
			printf("%c", sentence[i]);
		}
	}
	printf(".\n");
}

void print_dates(char **text, int *sentenceCount) {
	for (int s = 0; s < *sentenceCount; s++) {
		if (is_dates(text[s])) {
			func_dates(text[s]);
		}
	}
}

int len_words(char *sentence) {
	int count_words = 0, count = 0, len = 0;
	for (int i = 0; i < strlen(sentence) + 1; i++) {
		if (isalpha(sentence[i])) {
			count++;
		}
		else {
			if (isdigit(sentence[i]) == 0 && sentence[i] != '/') {
				len++;
			}
			if (count % 2 == 1) {
				count_words++;
			}
			count = 0;
		}
	}
	if (count_words == len) {
		return 1;
	}
	else {
		return 0;
	}
}

void remove_odd_let_count(char **text, int *quantity) {
	int count = 0;
	for (int i = 0; i < *quantity; i++) {
		if (len_words(text[i]) == 0) {
			text[count++] = text[i];
		}
	}
	*quantity = count;
}

void count_letters(char **text, int *quantity) {
	int capacity = 10;
	char *word = (char*)calloc(capacity, sizeof(char));
	int letters = 0, index = 0;
	for (int s = 0; s < *quantity; s++) {
		for (int i = 0; i < strlen(text[s]) + 1; i++) {
			if (text[s][i] != ' ' && text[s][i] != END_LINE && text[s][i] != ',') {
				word[index] = text[s][i];
				if (index + 1 >= capacity) {
					capacity *= 2;
					word = (char*)realloc(word, capacity * sizeof(char));
				}
				if (isalpha(text[s][i])) {
					letters++;
				}
			}
			else if (text[s][i] == ' ') {
				if (letters > 0) {
					printf("%d%s ", letters, word);
					letters = 0;
					index = -1;
				}
				else {
					printf("%s ", word);
					index = -1;
				}
				word = (char*)calloc(capacity, sizeof(char));
			}
			else if (text[s][i] == ',') {
				if (letters > 0) {
					printf("%d%s,", letters, word);
					letters = 0;
					index = -1;
				}
				else {
					printf("%s,", word);
					index = -1;
				}
				word = (char*)calloc(capacity, sizeof(char));
			}
			else {
				if (letters > 0) {
					printf("%d%s", letters, word);
					letters = 0;
					index = -1;
				}
				else {
					printf("%s", word);
					index = -1;
				}
				word = (char*)calloc(capacity, sizeof(char));
			}
			index++;
		}
		printf(".\n");
	}
	free(word);
}

int len_last_word(char *sentence) {
	int len = -1;
	int index = strlen(sentence);
	while (sentence[index] != ' ' && sentence[index] != ',' && index >= 0) {
		len++;
		index--;
	}
	return len;
}

int cmp(const void *a, const void *b) {
	return len_last_word(*(char**)a) - len_last_word(*(char**)b);
}

void sort_last(char **text, int *quantity) {
	qsort(text, *quantity, sizeof(char*), cmp);
	for (int i = 0; i < *quantity; i++) {
		printf("%s.\n", text[i]);
	}
}

void print_sentences(char** text, int *quantity) {
	for (int i = 0; i < *quantity; i++) {
		if (text[i][0] != END_LINE) {
			printf("%s.\n", text[i]);
		}
	}
}

char* join(char **text, int *quantity) {
	char *arr_text = (char*)malloc(sizeof(char));
	int capacity = 10;
	int symbol = 0;
	arr_text[symbol++] = ' ';
	for (int i = 0; i < *quantity; i++) {
		for (int j = 0; j < strlen(text[i]); j++) {
			if (symbol + 2 >= capacity) {
				capacity *= 2;
				arr_text = (char*)realloc(arr_text, capacity * sizeof(char));
			}
			if (text[i][j] == ',') {
				arr_text[symbol] = ' ';
				symbol++;
			}
			else {
				arr_text[symbol] = tolower(text[i][j]);
				symbol++;
			}
		}
		arr_text[symbol++] = ' ';
		arr_text[symbol++] = ' ';
	}
	return arr_text;
}

int substrCount(char * arr_text, char * substr)
{
	int counter = 0;

	while (1)
	{
		arr_text = strstr(arr_text, substr);
		if (!arr_text)
			break;
		++counter;
		arr_text += strlen(substr);
	}

	return counter;
}

void seek(char **text, int *quantity, char *arr_text) {
	int capacity = 10;
	char *word = (char*)calloc(capacity, sizeof(char));
	int symbol = 0;
	word[symbol++] = ' ';
	for (int i = 0; i < *quantity; i++) {
		int counter = 0;
		for (int j = 0; j < strlen(text[i]) + 1; j++) {
			if (symbol + 1 >= capacity) {
				capacity *= 2;
				word = (char*)realloc(word, capacity * sizeof(char));
			}
			if (text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '\0') {
				word[symbol++] = ' ';
				word[symbol] = '\0';
				if (substrCount(arr_text, do_low(word)) == 1) {
					if (counter != 0) {
						printf(" ");
						for (int l = 1; l < strlen(word) - 1; l++) {
							printf("%c", word[l]);
						}
					}
					else {
						for (int l = 1; l < strlen(word) - 1; l++) {
							printf("%c", word[l]);
						}
					}
					counter++;
				}
				symbol = 0;
				word = (char*)calloc(capacity, sizeof(char));
				word[symbol++] = ' ';
			}
			else {
				word[symbol] = text[i][j];
				symbol++;
			}
		}
		if (counter > 0) {
			printf(".\n");
		}
	}
}

void choice(int command) {
	if (command == 5) {
		printf("function info:\n\
        	1 - Displays all sentences that contain dates in the format “DD/MM/YYYY”, dates that have not yet arrived are highlighted in red.\n\
        	2 - Removes all sentences in which each word contains an odd number of letters.\n\
        	3 - Transforms sentences so that each word is preceded by the number of letters in it.\n\
        	4 - Sorts sentences in ascending order of the length of the last word.\n");
		return;
	}
	int *quantity = (int*)malloc(sizeof(int));
	*quantity = 0;
	char* arr_text = input(quantity);
	char** text = split_text(arr_text, quantity);
	text = remove_replays(text, quantity);
	switch (command) {
	case 0:
		print_sentences(text, quantity);
		break;
	case 1:
		print_dates(text, quantity);
		break;
	case 2:
		remove_odd_let_count(text, quantity);
		print_sentences(text, quantity);
		break;
	case 3:
		count_letters(text, quantity);
		break;
	case 4:
		sort_last(text, quantity);
		break;
	case 9:
		arr_text = join(text, quantity);
		seek(text, quantity, arr_text);
		break;
	default:
		printf("Error: Invalid command\n");
		break;
	}
	free(text);
}

int main() {
	printf(AUTHOR_INFO);
	int command = 6;
	scanf("%d", &command);
	choice(command);
	return 0;
}