#include"max.h"

int max(int* arr, int size) {

	int i = 0;
	int mx = arr[0];
	for(i; i < size; i++) {
		if (arr[i] > mx) {
			mx = arr[i];
		}
	}
	return mx;
}
