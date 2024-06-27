#include "abs_min.h"

int abs_min(int arr[], int len_arr) {
	int min = abs(abs_max(arr, len_arr));
	for(int i = 0; i < len_arr; i++){
		if (abs(arr[i]) < abs(min)){
			min = arr[i];
		}
	}
	return min;
}
