#include <stdio.h>
#include <stdlib.h>

int abs_min_i(int* m, int n) {
	int min_el = 0;
	for (int i = 1; i < n; i++) {
		if (abs(m[min_el]) > abs(m[i])) {
			min_el = i;
		}
	}
	return min_el;
}

int abs_min(int* m, int n) {
	return m[abs_min_i(m, n)];
}