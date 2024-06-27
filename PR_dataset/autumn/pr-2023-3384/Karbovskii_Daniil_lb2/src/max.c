#include <stdio.h>
#include "max.h"
int max(int arr[], int N) {
	int max = arr[0];
	for (int i = 1; i < N; i++) {
 	if (arr[i] > max)
	max = arr[i];
 	}
 return max;
}
