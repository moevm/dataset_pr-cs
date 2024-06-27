#include "sum.h"
#include "min.h"

int sum(int arr[], int size) {
	int sum = 0, k = 0;
	while (k < size && arr[k] != min(arr, size)) {
		sum += arr[k];
		k++;
	}
	return sum;
}
