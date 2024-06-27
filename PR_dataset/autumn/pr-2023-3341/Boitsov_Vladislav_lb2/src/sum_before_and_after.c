#include<stdio.h>
#include"index_first_zero.h"
#include"index_last_zero.h"
#include <stdlib.h>
#define ANS "%d\n"
void print_sum_before_and_after(int array_real_size, int array[])
{
	int sum=0;
	for(int i=0;i<get_index_first_zero(array_real_size, array);i++)
		sum+=abs(array[i]);
	for(int i=get_index_last_zero(array_real_size, array);i<array_real_size;i++)
		sum+=abs(array[i]);
	printf(ANS, sum);
}