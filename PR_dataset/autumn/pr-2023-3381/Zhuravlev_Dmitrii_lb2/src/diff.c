#include <stdlib.h>
#include <limits.h>
#include "abs_max.h"
#include "abs_min.h"

int diff(int* arr, int len) {
	int max_ind = abs_max(arr, len);
	int min_ind = abs_min(arr, len);
	return arr[max_ind] - arr[min_ind];
}