#include "sum.h"
#include "min.h"


int sum(int arr[], int size) {
	int mn = min(arr, size);
	int summ = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] == mn) {
			break;
		}
		summ += arr[i];
	}
	return summ;
}
