#include <stdio.h>
#include <stdlib.h>

#define N 100
int index_first_negative(int array[], int n) {
	int output_value;
	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			output_value = i;
			break;
		}
	}
	return output_value;
}

int index_last_negative(int array[], int n) {
	int output_value;
	for (int i = n - 1; i >= 0; i--) {
		if (array[i] < 0) {
			output_value = i;
			break;
		}
	}
	return output_value;
}

int sum_between_negative(int array[], int n) {
	int output_value = 0;
	for (int i = index_first_negative(array, n); i < index_last_negative(array, n); i++) {
		output_value += abs(array[i]);
	}
	return output_value;
}

int sum_before_and_after_negative(int array[], int n) {
	int array_sum = 0;
	for (int i = 0; i < n; i++) {
		array_sum += abs(array[i]);
	}
	return array_sum - sum_between_negative(array, n);
}

int main() {
	int arr[N];
	int size = 0;
	int value;
	scanf("%d", &value);
	while (getchar() != '\n') {
		scanf("%d", &arr[size]);
		size = size + 1;
	}

	switch (value) {
	case 0:
		printf("%d\n", index_first_negative(arr, size));
		break;
	case 1:
		printf("%d\n", index_last_negative(arr, size));
		break;
	case 2:
		printf("%d\n", sum_between_negative(arr, size));
		break;
	case 3:
		printf("%d\n", sum_before_and_after_negative(arr, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}
