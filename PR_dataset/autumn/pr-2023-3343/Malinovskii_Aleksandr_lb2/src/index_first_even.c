#include "index_first_even.h"
int index_first_even(int arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		if (abs(arr[i]) % 2 == 0) 
			return i;
	}
}
