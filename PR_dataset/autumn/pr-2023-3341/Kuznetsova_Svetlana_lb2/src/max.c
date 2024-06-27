#include "max.h"

int max(int arr[], int size) {
	int max = -100000;
	for (int k = 0; k < size; k++) {
		if (arr[k] > max) {
			max = arr[k];
		}
	}
	return max;
}
