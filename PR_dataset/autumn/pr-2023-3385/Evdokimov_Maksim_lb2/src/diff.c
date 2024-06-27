#include "abs_max.h"
#include "abs_min.h"

int diff(int* m, int n) {
	return abs_max(m,n) - abs_min(m,n);
}