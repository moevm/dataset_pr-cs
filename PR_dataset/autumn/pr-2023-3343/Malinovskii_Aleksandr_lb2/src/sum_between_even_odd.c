#include "sum_between_even_odd.h"
#include"index_first_even.h"
#include"index_last_odd.h"
int sum_between_even_odd(int arr[], int size)
{
	int sum_between_even_odd = 0;
	for (int i = 0; i < size; i++)
	{
		if ((i >= index_first_even(arr,size)) && (i < index_last_odd(arr,size)))
			sum_between_even_odd += abs(arr[i]);
	}
	return sum_between_even_odd;
}
