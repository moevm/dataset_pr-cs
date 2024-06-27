#include "sum_before_and_after.h"
int sum_before_and_after(int arr[], int arr_len)
{
	int result = 0;
	for(int i = 0; i < index_first_zero(arr, arr_len); i++) {result += abs(arr[i]);}
	for(int i = index_last_zero(arr, arr_len); i < arr_len; i++) {result += abs(arr[i]);}
	return result;
}
