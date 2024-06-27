#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"

int diff(int arr[], int arr_elements_quantity){
	int res=abs_max(arr,arr_elements_quantity)-abs_min(arr,arr_elements_quantity);
	return res;
}