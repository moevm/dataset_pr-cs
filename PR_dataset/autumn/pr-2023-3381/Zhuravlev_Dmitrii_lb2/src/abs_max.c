#include <limits.h>
#include <stdlib.h>

int abs_max(int* arr, int len) {
	int maxx = INT_MIN;
	int index_max;
	for (int i = 0; i < len; i++) {
		if (abs(arr[i]) > abs(maxx)) {
			maxx = arr[i];
			index_max = i;
		}
	}
	return index_max;
}