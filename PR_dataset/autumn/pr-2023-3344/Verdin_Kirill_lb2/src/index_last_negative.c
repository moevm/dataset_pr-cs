#include "index_last_negative.h"


int index_last_negative(int array[], int n) {
	int output_value;
	for (int i = n - 1; i >= 0; i--) {
		if (array[i] < 0) {
			output_value = i;
			break;
		}
	}
	return output_value;
}
