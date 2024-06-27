#include "sum_between.h"
int sum_between(int arr[], int arr_len)
{
	int result = 0;
	for(int i = index_first_zero(arr, arr_len)+1; i < index_last_zero(arr, arr_len); i++) {result += abs(arr[i]);}
	return result;
}
