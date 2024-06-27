#include "index_first_negative.h"

int index_first_negative(int arr[], int arr_count_items){
	for (int x = 0; x < arr_count_items; x++){
		if (arr[x] < 0){
			return x;
			break;
		}
	}
	return -1;
}
