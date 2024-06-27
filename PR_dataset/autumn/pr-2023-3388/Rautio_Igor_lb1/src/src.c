#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARRAY_LEN 100
#define CHAR_BUFFER_LEN 256

char input[CHAR_BUFFER_LEN];
int option;
int numbers[MAX_ARRAY_LEN]; 
int i = 0;

#define WORK(func) printf("%d\n", func(numbers, i));

int findMax(int numbers[], int length) {
	int max = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	return max;
}

int findMin(int numbers[], int length) {
	int min = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	return min;
}

int findDiff(int numbers[], int length) {
	return findMax(numbers, length) - findMin(numbers, length);
}

int findSumBeforeMin(int numbers[], int length) {
	int min = findMin(numbers, length);
	int sum = 0;
	for (int i = 0; i < length; i++) {
		if (numbers[i] == min) {
			break;
		}
		sum += numbers[i];
	}
	return sum;
}

int get_data() {
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

		return option;
	}
	else {
		printf("Ошибка при чтении ввода\n");
		return -1;
	}
}

void work_with_data(int option) {
	switch (option) {
		case 0:
			WORK(findMax)
			break;
		case 1:
			WORK(findMin);
			break;
		case 2:
			WORK(findDiff);
			break;
		case 3:
			WORK(findSumBeforeMin);
			break;
		default:
			printf("Данные некорректны\n");
	}
}

int main() {
	int option = get_data();
	if (option == -1) return 1;

	work_with_data(option);

	return 0;
}
