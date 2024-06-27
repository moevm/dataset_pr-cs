#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_before_even_and_after_odd(int arr[], int len){
	int first = index_first_even(arr, len);
        int last = index_last_odd(arr, len);
    	int sum = 0;
	int i;
    	for(i = 0; i < len; i++){
        	if((i < first) || (i >= last)){
            		sum += abs(arr[i]);
        	}
    	}
	return sum;
}
