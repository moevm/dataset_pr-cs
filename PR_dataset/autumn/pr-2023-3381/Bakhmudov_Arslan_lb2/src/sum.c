#include "macros.h"
#include "min.h"
#include "sum.h"


int sum(int nums[SIZE], int start, int stop)
{
	int res = 0;
	int stopindex = min_index(nums, start, stop);
	for(int n = 1; n < stopindex; n++)
	{
		res += nums[n];
	}
	return res;
}

