#include "index_last_negative.h"

int index_last_negative(int arr[], int arr_count_items){
	for (int x = arr_count_items - 1; x > 0; x--){
		if (arr[x] < 0){
			return x;
			break;
		}
	}
	return -1;
}
