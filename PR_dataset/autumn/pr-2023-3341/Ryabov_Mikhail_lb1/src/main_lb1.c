#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGHT 100

int abs_max(int arr[], int size) {
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (abs(max) < abs(arr[i])) {
			max = arr[i];
		}
	}
	return max;
}

int abs_min(int arr[], int size) {
	int min = arr[0];
	for (int i = 0; i < size; i++) {
		if (abs(min) > abs(arr[i])) {
			min = arr[i];
		}
	}
	return min;
}

int diff(int arr[], int size) {
	return abs_max(arr, size) - abs_min(arr, size);
}

int sum(int arr[], int size) {
	int max = abs_max(arr, size);
	int sum_num = 0;

	for (int i = 0; i < size; i++) {
		if (arr[i] == max) {
			for (int j = i; j < size; j++) {
				sum_num += arr[j];
			}
			break;
		}
	}
	return sum_num;
}

int main(){
	int array[MAX_LENGHT];
	int input;
	int size_array = 0;
	char space = ' ';

	scanf("%d", &input);
	while (size_array < MAX_LENGHT && space == ' ') {
		scanf("%d%c", &array[size_array], &space);
		size_array++;
	}

	switch (input)
	{
	case 0:
		printf("%d\n", abs_max(array, size_array));
		break;
	case 1:
		printf("%d\n", abs_min(array, size_array));
		break;
	case 2:
		printf("%d\n", diff(array, size_array));
		break;
	case 3:
		printf("%d\n", sum(array, size_array));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
}