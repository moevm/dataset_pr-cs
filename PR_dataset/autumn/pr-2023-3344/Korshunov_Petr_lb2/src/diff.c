#include "max.h"
#include "min.h"


int get_diff(int arr[], int arr_len)
{
	int diff = get_max(arr, arr_len) - get_min(arr, arr_len);
	return diff;
}