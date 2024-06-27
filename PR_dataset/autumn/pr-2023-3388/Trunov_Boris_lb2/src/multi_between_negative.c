#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int arr_count_items){
	int first_negative = index_first_negative(arr, arr_count_items);
	int last_negative = index_last_negative(arr, arr_count_items);
	int multi_result = 1;
	for (int x = first_negative; x < last_negative; x++){
		multi_result *= arr[x];
	}
	return multi_result;
}
