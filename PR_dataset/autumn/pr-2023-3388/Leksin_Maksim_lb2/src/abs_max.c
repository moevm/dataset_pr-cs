#include "abs_max.h"

int abs_max(int arr[], int size) {
	int max = -99999, id_max = 0;
	for (int i = 0; i < size; i++) {
		if (abs(arr[i]) > max){
			max = abs(arr[i]);
			id_max = i;
		}
	}
	return id_max;
}

