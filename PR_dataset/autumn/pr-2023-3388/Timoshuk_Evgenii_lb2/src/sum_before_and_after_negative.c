#include <stdlib.h>
#include <stdio.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int array[], int count)
{
	int before_sum = 0;
	int after_sum = 0;
	for(int i = 1; i < index_first_negative(array, count)+1; i++)
	{
		before_sum += array[i];
	}
	for(int i = count; i > index_last_negative(array, count)+1; i--)
	{
		after_sum += abs(array[i-1]);
	}
	return  before_sum + after_sum;
	  
	
}

