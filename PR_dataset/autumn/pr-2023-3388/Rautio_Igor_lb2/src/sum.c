#include "sum.h"
#include "min.h"
int findSumBeforeMin(int numbers[], int length) {
	int min = findMin(numbers, length);
	int sum = 0;
	for (int i = 0; i < length; i++) {
		if (numbers[i] == min) {
			break;
		}
		sum += numbers[i];
	}
	return sum;
}
