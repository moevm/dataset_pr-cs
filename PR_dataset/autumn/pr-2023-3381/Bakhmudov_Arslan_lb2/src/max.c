#include "macros.h"
#include "max.h"


int max_index(int nums[SIZE], int start, int stop)
{
	int	res = 0,
		ind = -1;
	
	for(int i = start; i < stop; i++)
	{
		if(res < nums[i])
		{
			res = nums[i];
			ind = i;
		}
	}
	return ind;
}

