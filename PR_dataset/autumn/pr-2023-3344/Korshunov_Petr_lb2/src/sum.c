#include "min.h"


int get_sum_bf_min(int arr[], int arr_len)
{
	int sum = 0;
	int min = get_min(arr, arr_len);
	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] != min){
			sum += arr[i];
		}else{
			break;
		}
	}
	return sum;
}