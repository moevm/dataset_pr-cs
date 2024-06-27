#include "abs_max.h"

int sum(int* m, int n) {
	int s = 0;
	for (int i = abs_max_i(m, n); i < n; i++) {
		s += m[i];
	}
	return s;
}