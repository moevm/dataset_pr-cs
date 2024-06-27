#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL 256
#define A 65
#define z 122
#define ZERO 48
#define NINE 57
#define END_STR '\0'

char *input(int *quantity) {
	int text_size = 0;
	int capacity = 10;
	char *text = (char*)malloc(sizeof(char));
	char ch = getchar();

	while (1) {
		text[text_size] = ch;
		if (text_size + 1 >= capacity) {
			capacity *= 2;
			text = (char*)realloc(text, capacity * sizeof(char));
		}
		text_size++;
		if (ch == ';' || ch == '?' || ch == '.') {
			(*quantity)++;
		}
		if (ch == '!') {
			(*quantity)++;
			break;
		}
		ch = getchar();
	}
	return text;
}

char** split(char *text, int *quantity) {

	int length = strlen(text);
	int start = 0;
	char **arr = (char**)malloc((*quantity) * sizeof(char*));
	int lines = 0;
	arr[lines] = (char*)malloc(INITIAL * sizeof(char));

	for (int i = 0; i < length; i++) {
		if (text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == ';') {
			int k = 0;

			for (int j = start; j <= i; j++) {
				if (text[j] == '\n') {
					continue;
				}
				arr[lines][k] = text[j];
				k++;
			}
			arr[lines][k] = END_STR;
			lines++;
			arr[lines] = (char*)malloc(INITIAL * sizeof(char));
			start = i + 2;
		}
	}
	return arr;
}

int is_let(char **arr, int i, int j) {
	return (arr[i][j] >= A && arr[i][j] <= z);
}
int is_num(char **arr, int i, int j) {
	return (arr[i][j] >= ZERO && arr[i][j] <= NINE);
}
int let_num_let(char **arr, int i, int j) {
	return (is_let(arr, i, j) && is_num(arr, i, j - 1) && is_let(arr, i, j - 2));
}
int let_num_num_let(char **arr, int i, int j) {
	return (is_let(arr, i, j) && is_num(arr, i, j - 1) && is_num(arr, i, j - 2) && is_let(arr, i, j - 3));
}
int let_num_num_num_let(char **arr, int i, int j) {
	return (is_let(arr, i, j) && is_num(arr, i, j - 1) && is_num(arr, i, j - 2) && is_num(arr, i, j - 3) && is_let(arr, i, j - 4));
}

char delete_nums(char** arr, int* quantity, int* res) {
	for (int i = 0; i < (*quantity); i++) {
		for (int j = strlen(arr[i]) - 2; j > 0; j--) {
			if (let_num_let(arr, i, j) || let_num_num_let(arr, i, j) || let_num_num_num_let(arr, i, j)) {
				arr[i][0] = END_STR;
				(*res) -= 1;
				break;
			}
		}
	}
}
void output(char** arr, int* quantity, int* res) {

	for (int i = 0; i < (*quantity); i++) {
		if (arr[i][0] != END_STR)
			printf("%s\n", arr[i]);
	}
	printf("Количество предложений до %d и количество предложений после %d", (*quantity) - 1, (*res) - 1);
}

int main() {

	int *quantity = (int*)malloc(sizeof(int));
	*quantity = 0;

	char* text = input(quantity);
	char** arr = split(text, quantity);
	int *res = (int*)malloc(sizeof(int));
	*res = *quantity;

	delete_nums(arr, quantity, res);
	output(arr, quantity, res);
}