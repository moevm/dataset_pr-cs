#include "sum_before_and_after_negative.h"
int sum_before_and_after_negative(int *arr, int size){
	int to_left, from_right;
	to_left = index_first_negative(arr, size);
	from_right = index_last_negative(arr, size);
	return summ_arr(arr, 0, to_left) + summ_arr(arr, from_right, size);
}
