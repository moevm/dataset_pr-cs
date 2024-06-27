#include "sum_between_even_odd.h"

int sum_between_even_odd(int* arr, int len){

	int even = index_first_even(arr, len);
	int odd = index_last_odd(arr, len);

	int sum = 0;
	for(int i = even; i < odd; i++){
		sum += abs(arr[i]);
	}

	return sum;
}
