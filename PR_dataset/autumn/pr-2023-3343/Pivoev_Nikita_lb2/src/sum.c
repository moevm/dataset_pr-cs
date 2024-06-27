#include "min.h"
int sum(int *array, int sizeOfArray) {
	int sum = 0;
	int minimum = min(array, sizeOfArray);
	for (int i = 0; i < sizeOfArray; ++i) {
		if (minimum != array[i])
			sum += array[i];
		else
			break;
	}
	return sum;
}
