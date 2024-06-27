#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#define N 100 

int index_first_even(int* array) {
	int first_index_even;
	for (int i = 0; i < N; i++) {
		if (abs(array[i]) % 2 == 0) {
			first_index_even = i;
			break;
		}
	}
	return first_index_even;
}

int index_last_odd(int* array) {
	int last_index_odd;
	for (int i = 0; i < N; i++) {
		if (abs(array[i]) % 2 == 1) {
			last_index_odd = i;
		}
	}
	return last_index_odd;
}

int sum_between_even_odd(int* array) {
	int sum_between_even_odd = 0;
	for (int i = index_first_even(array); i < index_last_odd(array); i++) {
		sum_between_even_odd += abs(array[i]);
	}
	return sum_between_even_odd;
}

int sum_before_even_and_after_odd(int* array) {
	int sum_before_even_after_odd = 0;
	for (int i = 0; i < index_first_even(array); i++) {
		sum_before_even_after_odd += abs(array[i]);
	}
	for (int i = index_last_odd(array); i < N; i++) {
		sum_before_even_after_odd += abs(array[i]);
	}
	return sum_before_even_after_odd;
}

int input_action(void) {
	char value;
	scanf("%c", &value);
	return value;
}

int* input_array(void) {
	static int array[N];
	int i = 0;
	char space = ' ';
	while (i < N && space == ' ') {
		scanf("%d%c", &array[i], &space);
		i++;
	}
	for (i; i < N; i++) {
		array[i] = 0;
	}
	return array;
}

int action(char value, int* array) {
	switch (value) {
	case '0':
		printf("%d\n", index_first_even(array));
		break;
	case '1':
		printf("%d\n", index_last_odd(array));
		break;
	case '2':
		printf("%d\n", sum_between_even_odd(array));
		break;
	case '3':
		printf("%d\n", sum_before_even_and_after_odd(array));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}

int main(void) {
	char value = input_action();
	int* array = input_array();
	action(value, array);
	return 0;
}
