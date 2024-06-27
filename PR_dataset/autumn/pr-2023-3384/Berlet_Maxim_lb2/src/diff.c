#include "diff.h"
#include "max.h"
#include "min.h"
int diff(int arr[], int arr_len){
	int difference = (max(arr, arr_len) - min(arr, arr_len));
	return difference;
}
