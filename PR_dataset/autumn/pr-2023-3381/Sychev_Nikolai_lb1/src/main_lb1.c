#include <stdio.h>
#include <stdlib.h>
#define N 100

int abs_max(int arr[], int count) { 
	int max_number = 0, result = 0;
	for (int i = 0; i < count; i++) {
		if (abs(arr[i]) > max_number) {
			max_number = abs(arr[i]);
			result = arr[i];
		}
	}
	return result;
}


int abs_min(int arr[], int count) {
	int min_number = abs(arr[0]), result = 0;
	for (int i = 1; i < count; i++) {
		if (abs(arr[i]) < min_number) {
			min_number = abs(arr[i]);
			result = arr[i];
		}
	}
	return result;
}


int diff(int arr[], int count) {
	int result = 0;
	result = abs_max(arr, count) - abs_min(arr, count);
	return result;
}


int sum(int arr[], int count) {
	int max_number = abs_max(arr, count);
	int fl = 0, result = 0;
	for (int i = 0; i < count; i++) {
		if (arr[i] == max_number && fl == 0) {
			fl = 1;
		}
		if (fl == 1) {
			result += arr[i];
		}
	}
	return result;
}


int main() {
	int count = 0;
	int arr[N], key;
	char space;

	scanf("%d%c", &key, &space);
	while (count < 100 && space != '\n') {
		scanf("%d%c", &arr[count], &space);
		count++;
	}

	switch (key) {
	case 0:
		printf("%d\n", abs_max(arr, count));
		break;
	case 1:
		printf("%d\n", abs_min(arr, count));
		break;
	case 2:
		printf("%d\n", diff(arr, count));
		break;
	case 3:
		printf("%d\n", sum(arr, count));
		break;
	default:
		printf("Данные некорректны\n");
	};
}