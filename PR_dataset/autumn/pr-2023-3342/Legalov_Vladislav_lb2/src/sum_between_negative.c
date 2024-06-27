#include "sum_between_negative.h"
int sum_between_negative(int *arr, int size){
	return summ_arr(arr, index_first_negative(arr, size), index_last_negative(arr, size));
}
