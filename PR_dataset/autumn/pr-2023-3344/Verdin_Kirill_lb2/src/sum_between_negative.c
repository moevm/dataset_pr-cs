#include "sum_between_negative.h"


int sum_between_negative(int array[], int n) {
	int output_value = 0;
	for (int i = index_first_negative(array, n); i < index_last_negative(array, n); i++) {
		output_value += abs(array[i]);
	}
	return output_value;
}
