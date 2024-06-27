#include "sum_before_and_after.h"

int sum_before_and_after(int arr[], int size)
{
	int first_zero_index = index_first_zero(arr, size);
	int last_zero_index = index_last_zero(arr, size);
	int sum_before = 0;
	for (int i = 0; i < first_zero_index; i++){
		sum_before += abs(arr[i]);
	}

	int sum_after = 0;

	for (int i = last_zero_index + 1; i < size; i++){
		sum_after += abs(arr[i]);
	}

	return sum_before + sum_after;
}
