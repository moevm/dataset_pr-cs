#include "max.h"

int max(int a[], int size){
	int mx = a[0];
	for (int i = 0; i < size; i++) {
		if (a[i] > mx) {
			mx = a[i];
		}
	}
	return mx;
}