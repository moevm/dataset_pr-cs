#include "sum.h"
#include "abs_max.h"



int sum(int arr[], int arr_elements_quantity){
	int max_abs_index=0;
	int max_abs=abs_max(arr,arr_elements_quantity);
	int res=0;
	while (max_abs!=arr[max_abs_index]){
		max_abs_index++;
	}
	for (max_abs_index; max_abs_index<arr_elements_quantity; max_abs_index++){
		res+=arr[max_abs_index];
	}
	return res;
}