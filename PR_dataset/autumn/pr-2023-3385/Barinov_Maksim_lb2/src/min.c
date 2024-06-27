#include <stdio.h>
#include "min.h"

int min(int n, int* arr) {
	int m = arr[0], i = 1;
	for (; i < n; i++) {
		if (arr[i] < m) m = arr[i];
	}
	return m;
}
