#include "index_last_odd.h"
int index_last_odd(int arr[], int size_arr)
{
int index = 0;
	for (int i = size_arr - 1;i >= 0; i--)
	{
		if (abs(arr[i]) % 2 != 0)
		{
			index = i;
			return index;
		}
	}
}

