#include "min.h"
int min(int arr[], int arr_len){
	int min_num = arr[0];
	for(int j = 1; j < arr_len; j++){
		if(arr[j] < min_num){
			min_num = arr[j];
		}
	}
	return min_num;
	}
