#include "sum_between.h"

int sum_between(int arr[], int size)
{
	int first_zero_index = index_first_zero(arr, size);
	int last_zero_index = index_last_zero(arr, size);
	int sum = 0;

	for (int i = first_zero_index + 1; i < last_zero_index; i++){
		sum += abs(arr[i]);
	}

	return sum;
}
