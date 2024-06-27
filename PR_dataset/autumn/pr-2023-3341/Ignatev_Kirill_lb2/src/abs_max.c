#include <stdlib.h>
#include "abs_max.h"

int abs_max(int arr[],int  arr_elements_quantity){
	int max_abs=-1e9;
	int res=0;
	for (int k=0; k<arr_elements_quantity; k++){
		if (abs(arr[k])>max_abs){
			max_abs=abs(arr[k]);
			res=arr[k];
		}
	}
    return res;

}