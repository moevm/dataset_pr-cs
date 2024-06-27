#include <stdlib.h>

#include "index_first_zero.h"
#include "index_last_zero.h"

#include "sum_between.h"


int sum_between(int arr[], int size){
	int first_index = index_first_zero(arr, size);
	int last_index = index_last_zero(arr, size);
	int sum = 0;
	for (int i = first_index; i <= last_index; ++i){
		sum += abs(arr[i]);
	}
	return sum;
}
