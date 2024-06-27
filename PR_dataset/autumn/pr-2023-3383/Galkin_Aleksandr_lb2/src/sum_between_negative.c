#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int arr[], int n){
	int first=index_first_negative(arr, n);
	int last=index_last_negative(arr, n);
	int sum = 0;
	for(int i = first; i<last; i++){
		sum  = sum + abs(arr[i]);
	}
	return sum;
}
