#include "summ_arr.h"
int summ_arr(int *arr, int left, int right){
	int res = 0;
	for(int i = left; i < right; ++i)
		res = res + abs(arr[i]);
	return res;
}
