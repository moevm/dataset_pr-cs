#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int abs_max(int arr[], int len) {
	int maxx = INT_MIN;
	for (int i = 0; i < len; i++) {
		if (abs(arr[i]) > abs(maxx)) maxx = arr[i];
	}
	return maxx;
}

int abs_min(int arr[], int len) {
	int minn = INT_MAX;
	for (int i = 0; i < len; i++) {
		if ((abs(arr[i])) < abs(minn)) minn = arr[i];
	}
	return minn;
}

int diff(int arr[], int len) {
	int maxx = abs_max(arr, len);
	int minn = abs_min(arr, len);
	return maxx - minn;
}

int sum(int arr[], int len) {
	int maxx = abs_max(arr, len);
	int summ = 0;
	short flag = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] == maxx) flag = 1;
		if (flag) summ += arr[i];
	}
	return summ;
}

int main() {
	int instruction;
	scanf("%d", &instruction);

	int input_array[100] = {};
	char after_number;
	int lenght = 0;
	for (int i = 0; i < 100; i++) {
		scanf("%d", &input_array[i]);
		lenght++;
		after_number = getchar();
		if (after_number == '\n') break;
	}

	switch (instruction) {
		case 0:
			printf("%d\n", abs_max(input_array, lenght));
			break;
		case 1:
			printf("%d\n", abs_min(input_array, lenght));
			break;
		case 2:
			printf("%d\n", diff(input_array, lenght));
			break;
		case 3:
			printf("%d\n", sum(input_array, lenght));
			break;
		default:
			printf("Данные некорректны\n");
	}	
}