#include <stdio.h>
#include "min.h"

int sum(int n, int* arr) {
	int m = min(n, arr), s = 0,i = 0;
	for (; i < n; i++) {
		if (arr[i] == m) break;
		s += arr[i];
	}
	return s;
}
