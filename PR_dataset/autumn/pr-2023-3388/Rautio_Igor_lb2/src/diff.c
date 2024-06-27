#include "diff.h"
#include "max.h"
#include "min.h"
int findDiff(int numbers[], int length) {
	return findMax(numbers, length) - findMin(numbers, length);
}

