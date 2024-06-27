#include "max.h"

int max(int arr[], int n){
	int maxx = arr[0], i;
	for (i = 1; i < n; i++)
		if (arr[i] > maxx)
			maxx = arr[i];
	return maxx;
}
