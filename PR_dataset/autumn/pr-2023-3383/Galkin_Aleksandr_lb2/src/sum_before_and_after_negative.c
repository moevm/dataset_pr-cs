#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int arr[], int n){
	int first = index_first_negative(arr,n);
	int last = index_last_negative(arr,n);
	int sum = 0;
	for(int i = 0; i<first; i++){
		sum = sum + abs(arr[i]);
	}
	for(int i = last; i<n; i++){
		sum = sum + abs(arr[i]);
	}
	return sum;
}
