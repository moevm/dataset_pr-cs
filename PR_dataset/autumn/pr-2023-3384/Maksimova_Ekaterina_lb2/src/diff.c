#include"diff.h"

int diff(int* arr, int size) {

	int mx, mn, differ;
	mx = max(arr, size);
	mn = min(arr, size);
	differ = mx - mn;
	return differ;
}

