#include "index_last_odd.h"
int index_last_odd(int arr[], int size) {
	int ind = 0;
	for (int i =0; i<size; i++) 
	{
		if (abs(arr[i]) % 2 != 0) 
			ind=i;
	}
	return ind;
}
