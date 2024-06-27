#include "sum_before_even_and_after_odd.h"

int sum_before_even_and_after_odd(int* arr, int len){

	int even = index_first_even(arr, len);
	int odd = index_last_odd(arr, len);

	int sum = 0;
	for(int i = 0; i < even; i++){
		sum += abs(arr[i]);
	}
	for(int i = odd; i < len; i++){
		sum += abs(arr[i]);
	}

	return sum;
}
