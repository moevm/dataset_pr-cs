#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int arr[], int l){
	int sum=0;
	int index_f =index_first_negative(arr, l); 
	int index_l =index_last_negative(arr, l);
	int i;
	for(i=0; i<index_f;i++){
		sum = sum + abs(arr[i]);
	}	
	for(i=index_l;i<=l;i++){
		sum =  sum + abs(arr[i]);
	}	
	return sum;
}
