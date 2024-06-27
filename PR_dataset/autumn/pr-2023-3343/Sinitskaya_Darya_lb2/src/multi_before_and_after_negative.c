#include "multi_before_and_after_negative.h"
#include"index_first_negative.h"
#include"index_last_negative.h"
int multi_befor_and_after_negative(int *arr_of_integers, int counter)
{
	int f2_index=index_first_negative(arr_of_integers, counter); // индекс первого отрицательного э-та массива
	int l2_index=index_last_negative(arr_of_integers, counter); // индекс последнего отрицательного э-та массива
	int composition2=1;
	for(int i=0;i<f2_index;i++)
	{
		composition2*=arr_of_integers[i];
	}
	for(int i=l2_index;i<counter;i++)
	{
		composition2*=arr_of_integers[i];
	}
	return composition2;
}
