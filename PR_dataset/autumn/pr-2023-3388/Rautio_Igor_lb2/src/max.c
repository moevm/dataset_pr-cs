#include "max.h"

int findMax(int numbers[], int length) {
	int max = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	return max;
}
