#include "abs_min.h"

int abs_min(int arr[], int size) {
	int min = 99999, id_min = 0;
	for (int i = 0; i < size; i++) {
		if (abs(arr[i]) < min){
			min = abs(arr[i]);
			id_min = i;
		}
	}
	return id_min;
}

