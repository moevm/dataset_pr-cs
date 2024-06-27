#include "sum.h"
#include "min.h"


int sum(int arr[], int arr_len){
	int s = 0;
	for(int a = 0; a < arr_len; a++){
		if(arr[a] != min(arr, arr_len)){
			s += arr[a];
		}
		else return s;
}}
