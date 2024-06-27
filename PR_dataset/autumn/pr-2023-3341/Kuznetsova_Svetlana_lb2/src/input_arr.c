#include "input_arr.h"

int input_arr(int arr[]) {
	int size = 0, value;
	while (getchar() != '\n') {
		scanf("%d", &value);
		arr[size] = value;
		size++;
	}
	return size;
}
