#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int arr_count_items){
	int first_negative = index_first_negative(arr, arr_count_items);
	int last_negative = index_last_negative(arr, arr_count_items);
	int multi_result = 1;
	for (int x = 0; x < first_negative; x++){
		multi_result *= arr[x];
	}
	for (int x = last_negative; x < arr_count_items; x++){
		multi_result *= arr[x];
	}
	return multi_result;
}
