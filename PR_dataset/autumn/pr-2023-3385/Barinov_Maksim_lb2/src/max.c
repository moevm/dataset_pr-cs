#include <stdio.h>
#include "max.h"

int max(int n, int* arr) {
	int m = arr[0], i = 1;
	for (; i < n; i++) {
		if (arr[i] > m) m = arr[i];
	}
	return m;
}
