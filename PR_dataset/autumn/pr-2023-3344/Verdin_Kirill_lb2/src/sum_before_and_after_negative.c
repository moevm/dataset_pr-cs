#include "sum_before_and_after_negative.h"


int sum_before_and_after_negative(int array[], int n) {
	int array_sum = 0;
	for (int i = 0; i < index_first_negative(array, n); i++) {
		array_sum += abs(array[i]);
	}
	for (int i = index_last_negative(array, n); i < n; i++) {
		array_sum += abs(array[i]);
	}
	return array_sum;
}
