#include <stdlib.h>
#include <limits.h>

int abs_min(int* arr, int len) {
	int minn = INT_MAX;
	int index_min;
	for (int i = 0; i < len; i++) {
		if ((abs(arr[i])) < abs(minn)) {
			minn = arr[i];
			index_min = i;
		}
	}
	return index_min;
}