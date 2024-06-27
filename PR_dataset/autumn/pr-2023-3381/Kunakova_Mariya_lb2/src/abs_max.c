#include "abs_max.h"

int abs_max(int arr[], int len_arr) {
	int max = 0;
	for(int i = 0; i < len_arr; i++){
		if (abs(arr[i]) > abs(max)){
			max = arr[i];
		}
	}
	return max;
}
