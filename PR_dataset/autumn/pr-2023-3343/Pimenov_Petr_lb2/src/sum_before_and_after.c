#include <stdlib.h>

#include "index_first_zero.h"
#include "index_last_zero.h"

#include "sum_before_and_after.h"

int sum_before_and_after(int arr[], int size){
	int first_index = index_first_zero(arr, size);
	int last_index = index_last_zero(arr, size);
	int sum = 0;
	for (int i = 0; i <= first_index; ++i){
		sum += abs(arr[i]);
	}
	for (int j = last_index; j < size; ++j){
		sum += abs(arr[j]);
	}
	return sum;
}
