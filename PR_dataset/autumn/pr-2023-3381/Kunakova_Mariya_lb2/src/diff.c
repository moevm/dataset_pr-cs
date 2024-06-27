#include "diff.h"
int diff(int arr[], int len_arr) {
	int difference = abs_max(arr, len_arr) - abs_min(arr, len_arr);
	return difference;
}
