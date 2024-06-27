#include "index_last_negative.h"

int index_last_negative(int *array, int length)
{
	int ans = -1;
	for(int i = 0; i<length; i++)
	{
		if(array[i] < 0)
		ans = i;
	}
	return ans;
}
