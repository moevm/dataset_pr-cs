#include <stdio.h>
#include "min.h"
int min(int arr[], int N) {
	int min = arr[0];
	for (int i = 1; i < N; i++) {
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

