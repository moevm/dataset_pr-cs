#include "get_data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHAR_BUFFER_LEN 256
#define MAX_ARRAY_LEN 100

int get_data(int* numbers, int* length) {
	char input[CHAR_BUFFER_LEN];
	int option = -1;
	int i = 0;
	if (fgets(input, CHAR_BUFFER_LEN, stdin) != NULL) {
		char* token = strtok(input, " ");

		if (token != NULL) {
			option = atoi(token);
		}
		else {
			printf("Ошибка: значение option не найдено\n");
			return -1;
		}

		while ((token = strtok(NULL, " ")) != NULL && i < MAX_ARRAY_LEN) {
			numbers[i] = atoi(token);  
			i++;
		}
		(*length) = i;
		return option;
	}
	else {
		printf("Ошибка при чтении ввода\n");
		return -1;
	}
}
