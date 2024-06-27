#include"index_first_even.h"
#include"index_last_odd.h"
#include  <stdlib.h>



int sum_before_even_and_after_odd(int *arr, int len){
	int sum = 0;
	for(int i=0; i<index_first_even(arr, len);++i){
		sum += abs(arr[i]);
	}

	for(int i=index_last_odd(arr,len); i<len;++i){
		sum += abs(arr[i]);
	}
	return sum;
}
