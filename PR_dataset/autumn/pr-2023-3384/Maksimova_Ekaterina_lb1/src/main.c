#include<stdio.h>

int get_max(int* arr, int size) {

	int i = 0;
	int mx = arr[0];
	for(i; i < size; i++) {
		if (arr[i] > mx) {
			mx = arr[i];
		}
	}
	return mx;
}

int get_min(int* arr, int size) {

	int i = 0;
	int mn = arr[0];
	for(i; i < size; i++) {
		if(arr[i] < mn) {
			mn = arr[i];
		}
	}
	return mn;
}

int diff(int* arr, int size) {

	int mx, mn, differ;
	mx = get_max(arr, size);
	mn = get_min(arr, size);
	differ = mx - mn;
	return differ;
}

int get_sum(int* arr, int size) {
	int i = 0;
	int summa = 0;
	int mn;
	mn = get_min(arr, size);
	while (arr[i] != mn) {
		summa += arr[i];
		i++;
	}
	return summa;
}

int main() {
	int command;
	int size = 0;
	int arr[100];
	scanf("%d", &command);
	do {
		scanf("%d", &arr[size++]);
	} while (getchar() != '\n');
	switch (command) {
	case 0:
		printf("%d\n", get_max(arr, size));
		break;
	case 1:
		printf("%d\n", get_min(arr, size));
		break;
	case 2:
		printf("%d\n", diff(arr, size));
		break;
	case 3:
		printf("%d\n", get_sum(arr, size));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}