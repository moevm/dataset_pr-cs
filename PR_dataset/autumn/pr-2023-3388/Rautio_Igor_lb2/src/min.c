#include "min.h"
int findMin(int numbers[], int length) {
	int min = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	return min;
}
