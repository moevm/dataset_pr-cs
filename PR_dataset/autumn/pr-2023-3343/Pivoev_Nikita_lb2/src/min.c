#include <limits.h>
int min(int *array, int sizeOfArray) {
	int minimum = INT_MAX;
	for (int i = 0; i < sizeOfArray; ++i) {
		if (array[i] < minimum)
			minimum = array[i];
	}
	return minimum;
}
