#include <stdio.h>
#include <stdlib.h>

int abs_max_i(int* m, int n) {
	int max_el = 0;
	for (int i = 1; i < n; i++) {
		if (abs(m[max_el]) < abs(m[i])) {
			max_el = i;
		}
	}
	return max_el;
}

int abs_max(int* m, int n) {
	return m[abs_max_i(m, n)];
}