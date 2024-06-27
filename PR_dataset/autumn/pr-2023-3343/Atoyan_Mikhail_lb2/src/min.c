#include "min.h"

int min(int a[], int size) {
	int mn = a[0];
	for (int i = 0; i < size; i++) {
		if (a[i] < mn) {
			mn = a[i];
		}
	}
	return mn; 
}