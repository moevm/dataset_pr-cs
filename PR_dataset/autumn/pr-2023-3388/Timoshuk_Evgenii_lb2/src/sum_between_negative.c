#include <stdlib.h>
#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int arr[], int count)
{
	int total_sum = 0;
	for(int i = index_first_negative(arr, count) +1; i<index_last_negative(arr, count) +1; i++)
	{
		total_sum+=abs(arr[i]);
	}
	return total_sum;
}
