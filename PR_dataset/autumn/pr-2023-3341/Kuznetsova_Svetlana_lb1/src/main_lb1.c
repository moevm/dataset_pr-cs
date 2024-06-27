#include <stdio.h>

#define msize 100
int max(int arr[], int size) {
	int max = -100000;
	for (int k = 0; k < size; k++) {
		if (arr[k] > max) {
			max = arr[k];
		}
	}
	return max;
}
int min(int arr[], int size) {
	int min = 100000;
	for (int k = 0; k < size; k++) {
		if (arr[k] < min) {
			min = arr[k];
		}
	}
	return min;
}
int diff(int min, int max) {
	int dif = max - min;
	return dif;
}
int sum(int arr[], int min, int size) {
	int sum = 0, k = 0;
	while (k < size && arr[k] != min) {
		sum += arr[k];
		k++;
	}
	return sum;
}

int input_key() {
	int key;
	scanf("%d", &key);
	return key;
}

int input_arr(int arr[]) {
	int size = 0, value;
	while (getchar() != '\n') {
		scanf("%d", &value);
		arr[size] = value;
		size++;
	}
	return size;
}

int choice(int arr[], int size, int key) {
	int min_, max_;
	switch (key) {
	case 0:
		printf("%d\n", max(arr, size));
		break;
	case 1:
		printf("%d\n", min(arr, size));
		break;
	case 2:
		max_ = max(arr, size);
		min_ = min(arr, size);
		printf("%d\n", diff(min_, max_));
		break;
	case 3:
		min_ = min(arr, size);
		printf("%d\n", sum(arr, min_, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
}

int main() {
	int key, size, arr[msize];
	key = input_key();
	size = input_arr(arr);
	choice(arr, size, key);
}