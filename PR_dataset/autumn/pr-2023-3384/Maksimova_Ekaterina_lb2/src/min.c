#include"min.h"

int min(int* arr, int size) {

	int i = 0;
	int mn = arr[0];
	for(i; i < size; i++) {
		if(arr[i] < mn) {
			mn = arr[i];
		}
	}
	return mn;
}
