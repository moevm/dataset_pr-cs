#include "diff.h"

int diff(int a[], int size) {
	return max(a, size) - min(a, size);
}