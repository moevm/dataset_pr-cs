#include "index_first_negative.h"


int index_first_negative(int array[], int n) {
	int output_value;
	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			output_value = i;
			break;
		}
	}
	return output_value;
}
