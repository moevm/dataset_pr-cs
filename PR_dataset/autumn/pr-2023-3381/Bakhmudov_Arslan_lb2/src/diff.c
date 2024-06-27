#include "macros.h"
#include "max.h"
#include "min.h"
#include "diff.h"


int diff(int nums[SIZE], int start, int stop)
{
	int a = nums[max_index(nums, start, stop)];
	int b = nums[min_index(nums, start, stop)];
	return a - b;
}

