#include "min.h"

int min(int arr[], int size) {
	int min = 100000;
	for (int k = 0; k < size; k++) {
		if (arr[k] < min) {
			min = arr[k];
		}
	}
	return min;
}

