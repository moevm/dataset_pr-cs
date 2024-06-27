#include "max.h"
#include "min.h"
int diff(int *array, int sizeOfArray) {
	return max(array, sizeOfArray) - min(array, sizeOfArray);
}
