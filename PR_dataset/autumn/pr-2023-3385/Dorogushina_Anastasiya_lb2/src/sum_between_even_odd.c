#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[], int len){
	int first = index_first_even(arr, len);
	int last = index_last_odd(arr, len);
	int sum = 0;
    	int i;
    	for(i = first; i < last; i++){
        	sum += abs(arr[i]);
    	}
    	return sum;
}
