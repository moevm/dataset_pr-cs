#include <stdlib.h>
#include <limits.h>

int sum(int* arr, int len) {
	int max_ind = abs_max(arr, len);
	int summ = 0;
	short flag = 0;
	for (int i = max_ind; i < len; i++) {
		summ += arr[i];
	}
	return summ;
}