#include "max.h"
int max(int arr[], int arr_len){
	int max_num = arr[0];
	for(int z = 1; z < arr_len; z++){
		if(arr[z] > max_num){
			max_num = arr[z];
		}
	}
	return max_num;
	}
