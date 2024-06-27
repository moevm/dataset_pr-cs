#include <stdlib.h>
#include "abs_min.h"

int abs_min(int arr[], int arr_elements_quantity){
	int min_abs=1e9;
	int res=0;
	for (int k=0; k<arr_elements_quantity; k++){
		if(abs(arr[k])<min_abs){
			min_abs=abs(arr[k]);
			res=arr[k];
		}
	}

	return res;
}