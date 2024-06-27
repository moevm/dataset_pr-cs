#include "sum.h"

int sum(int a[], int size) {
	int mn = min(a, size);
	int s = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] == mn) {
			break;
		}
		s += a[i];
	}
	return s;
}