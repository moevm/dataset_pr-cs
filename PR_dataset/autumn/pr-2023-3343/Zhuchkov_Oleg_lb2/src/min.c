#include "min.h"

int min(int arr[], int n){
	int minn = arr[0], i;
	for (i = 1; i < n; i++)
		if (arr[i] < minn)
			minn = arr[i];
	return minn;
}
