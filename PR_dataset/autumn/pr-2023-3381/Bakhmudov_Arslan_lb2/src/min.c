#include "macros.h"
#include "min.h"


int min_index(int nums[SIZE], int start, int stop)
{
	int	res = 10005000,
		ind = -1;
	
	for(int i = start; i < stop; i++)
	{
		if(res > nums[i])
		{
			res = nums[i];
			ind = i;
		}
	}
	return ind;
}

